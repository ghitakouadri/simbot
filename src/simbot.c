/*
    simbot is a simulator of a 2 wheels differential drive robot.
    Copyright (C) 2014-2015 Roberto Cometti <modsrm@pagefault.io>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    You can find the full license document in the root of this repository
    or online at <http://www.gnu.org/licenses/gpl-2.0.html>
*/

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <sched.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <stdbool.h>

#include "graphics.h"
#include "scenario.h"
#include "robot.h"

#define UNUSED(x) (void)x

static struct Vertex cursor_position = {0.0, 0.0};

static struct simbot {

    const int window_length;
    const int window_height;
    struct Vertex destination;
    struct Vertex position;

} simbot_prog = {800, 800, {0.0, 0.0}, {0.0, 0.0}};

static void window_size_callback(GLFWwindow *window, int length, int height) {

    UNUSED(window);
    set_plane_size(length, height);
}

static void error_callback(int err_code, const char* description) {

    UNUSED(err_code);
    fputs(description, stderr);
}

static void window_to_cartesian_coord(double *x, double *y) {

    *x = *x - simbot_prog.window_length / 2;

    // The y coordinate is flipped because the window y coordinate grows towards
    // decreasing cartesian y values.
    *y = -(*y - simbot_prog.window_height / 2);
}

static void mouse_position_callback(GLFWwindow *window, double x, double y) {

    UNUSED(window);
    cursor_position.x = x;
    cursor_position.y = y;
}

static void set_simbot_destination() {

    double x = cursor_position.x;
    double y = cursor_position.y;

    window_to_cartesian_coord(&x, &y);

    simbot_prog.destination.x = x;
    simbot_prog.destination.y = y;

    printf("%s: Recorded destination: x=%f y=%f\n", __func__,
           simbot_prog.destination.x, simbot_prog.destination.y );
}

static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                  int mods) {

    UNUSED(window);
    UNUSED(button);
    UNUSED(mods);

    if(action == GLFW_PRESS)
    {
        set_simbot_destination();
    }
}

static void set_callbacks(GLFWwindow *window) {

    glfwSetErrorCallback(error_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_position_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
}

static GLFWwindow* init_window(const int window_length, const int window_height) {

    if(glfwInit() != GL_TRUE)
    {
        exit(EXIT_FAILURE);
    }

    GLFWwindow *main_window = glfwCreateWindow(window_length, window_height,
                                               "SimBot", NULL, NULL);

    if(!main_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(main_window);

    set_callbacks(main_window);

    return main_window;
}

static void prepare_to_draw_window(GLFWwindow *window) {

    int length = 0;
    int height = 0;
    // The size of the window needs to be refreshed because it might
    // have changed since the last time the buffers were swapped.
    glfwGetWindowSize(window, &length, &height);

    // The viewport maps the clipping area to an area of the window.
    // In this case, the viewport size is the whole window.
    glViewport(0, 0, length, height);

    // Clear window.
    glClearColor(0.75, 0.75, 0.75, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // The viewing volume is defined by the projection matrix.
    // The next call specifies that the projection matrix is the
    // target for the subsequent calls.
    glMatrixMode(GL_PROJECTION);

    // Each call to glOrtho results in a multiplication of the current
    // clipping volume by the matrix described by the args of glOrtho.
    // Loading the identity matrix will reset the current clipping volume,
    // hence the subsequent glOrtho call will set a clean clipping volume.
    glLoadIdentity();

    GLdouble half_x = length/2;
    GLdouble half_y = height/2;

    // glOrtho sets up the clipping volume.
    // The clipping volume can be seen as the coordinate system of choice.
    // The following call will set up the clipping volume so that the
    // center of the viewport will be the origin (0,0).
    glOrtho( -half_x, half_x, -half_y, half_y, 1, -1);

    // Set the current matrix to the model view. The modelview matrix
    // defines how the objects in the buffer are transformed (rotated,
    // translated, scaled).
    glMatrixMode(GL_MODELVIEW);

    // Reset all transformations.
    glLoadIdentity();
}

static bool is_window_open(GLFWwindow *window) {

    return glfwWindowShouldClose(window) == GL_FALSE;
}

static void finalize_draw_window(GLFWwindow *window) {

    glFlush();
    glfwSwapBuffers(window);

    static unsigned long count = 0;
    printf("%s: Paint %lu\n", __func__, ++count);
}

static void translate_robot() {

    printf("%s: translate to %f %f\n", __func__, simbot_prog.position.x, simbot_prog.position.y);
    glTranslated(simbot_prog.position.x, simbot_prog.position.y, 0.0);
}

static void rotate_robot(double angle) {

    if(!isnan(angle))
    {
        printf("%s: rotating at angle %f\n", __func__, angle);
        glRotated(angle, 0.0, 0.0, 1.0);
    }
}

static double get_destination_angle() {

    // Transform the vector identified by the current position and the
    // destination point into the component form <D - P>. A vector in component
    // form has the initial point at the origin of the axes.
    struct Vertex comp_form;
    comp_form.x = simbot_prog.destination.x - simbot_prog.position.x;
    comp_form.y = simbot_prog.destination.y - simbot_prog.position.y;

    // Calculate the angle between the vector in component form and the x axis.
    double direction = atan(comp_form.y / comp_form.x) * 180 / 3.14;

    // In order to calculate the angle between the x axis and the actual
    // destination, the direction needs to be adjusted if the component form is
    // in the second or third quadrant.
    if(comp_form.x < 0)
    {
        direction += 180;
    }

    return direction;
}

static void move_robot() {

    printf("%s: robot destination %f %f\n", __func__,
            simbot_prog.destination.x, simbot_prog.destination.y);

    translate_robot();

    double destination_angle = get_destination_angle();
    rotate_robot(destination_angle);
    draw_robot();
}

int main() {

    printf("%s: This is SimBot!\n", __func__);

    GLFWwindow *main_window = init_window(simbot_prog.window_length,
                                          simbot_prog.window_height);

    init_robot();

    while(is_window_open(main_window))
    {
        prepare_to_draw_window(main_window);

        draw_2d_cartesian_plane();

        move_robot();

        finalize_draw_window(main_window);
        glfwWaitEvents();
    }

    glfwTerminate();
}

