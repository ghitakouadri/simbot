/*
    simbot is a simulator of a 2 wheels differential drive robot.
    Copyright (C) 2014 Roberto Cometti <modsrm@gmail.com>

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

#include "graphics.h"

static const unsigned int X_LENGTH = 800;
static const unsigned int Y_LENGTH = 600;

static void error_callback(int, const char*);
static void draw_cartesian_axes(GLdouble half_x, GLdouble half_y);
static void draw_axes_directions(GLdouble half_x, GLdouble half_y);
static void mouse_button_callback(GLFWwindow*, int, int, int);

int main() {

    printf("This is SimBot!\n");

    // Set error callback for glfw.
    glfwSetErrorCallback(error_callback);

    // Initialize glfw.
    if(glfwInit() != GL_TRUE)
    {
        exit(EXIT_FAILURE);
    }

    // Create main windows.
    GLFWwindow *main_window = glfwCreateWindow(X_LENGTH, Y_LENGTH,
            "SimBot", NULL, NULL);

    if(!main_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(main_window);

    // Set viewport to whole window.
    int width = 0;
    int height = 0;
    glfwGetWindowSize(main_window, &width, &height);

    // Set mouse button callback.
    glfwSetMouseButtonCallback(main_window, mouse_button_callback);

    unsigned int count = 0;
    while(1)
    {

        // The viewport maps the clipping area to an area of the window.
        // In this case, the viewport size is the whole window.
        glViewport(0, 0, width, height);

        // Clear window.
        glClearColor(0.75, 0.75, 0.75, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        // The viewing volume is defined by the projection matrix.
        // The next call specifies that the projection matrix is the
        // target for the subsequent calls.
        glMatrixMode(GL_PROJECTION);

        // Each call to glOrtho results in a multiplication of the current
        // clipping volume by the matrix described by the args of glOrtho.
        // Loading the identity matrix will reset the current clipping volume,
        // hence the subsequent glOrtho call will set a clean clipping volume.
        glLoadIdentity();

        // The size of the window need to be refreshed because it might
        // have changed since the last time the buffers were swapped.
        glfwGetWindowSize(main_window, &width, &height);

        GLdouble half_x = width/2;
        GLdouble half_y = height/2;

        // glOrtho sets up the clipping volume.
        // The clipping volume can be seen as the coordinate system of choice.
        // The following call will set up the clipping volume so that the
        // center of the viewport will be the origin (0,0).
        glOrtho( -half_x, half_x, -half_y, half_y, 1, -1);

        // Set the current matrix to the model view. The modelview matrix
        // defines how the objects in the buffer are transformed (rotated,
        // translates, scaled).
        glMatrixMode(GL_MODELVIEW);

        // Reset all transformations.
        glLoadIdentity();

        draw_cartesian_axes(half_x, half_y);

        draw_axes_directions(half_x, half_y);

        glFlush();
        glfwSwapBuffers(main_window);

        printf("Paint %u\n", ++count);
        glfwWaitEvents();
    }

    // Terminate glfw.
    glfwTerminate();
}

static void draw_cartesian_axes(GLdouble half_x, GLdouble half_y) {

    // Draw cartesian axes.
    glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);

      // x axis.
      glVertex2s(-half_x, 0);
      glVertex2s(half_x, 0);

      // y axis.
      glVertex2s(0, -half_y);
      glVertex2s(0, half_y);
    glEnd();
}

static void draw_axes_directions(GLdouble half_x, GLdouble half_y) {

    // Draw axes' directions.
    unsigned int tri_side_px = 20;
    unsigned int half_tri_side_px = tri_side_px >> 1;

    struct vertices *vert = init_vertices(3);
    vert->verts[0].x = 0;
    vert->verts[0].y = half_y;
    vert->verts[1].x = - half_tri_side_px;
    vert->verts[1].y = vert->verts[2].y =
        half_y - get_tri_height_from_side(tri_side_px);

    vert->verts[2].x = half_tri_side_px;
    draw_triangle(tri_side_px, vert);

    vert->verts[0].x = half_x;
    vert->verts[0].y = 0;
    vert->verts[1].y = - half_tri_side_px;
    vert->verts[1].x = vert->verts[2].x =
        half_x - get_tri_height_from_side(tri_side_px);

    vert->verts[2].y = half_tri_side_px;
    draw_triangle(tri_side_px, vert);

    free(vert);
}

// TODO: add doc.
static void error_callback(int err_code, const char* description) {
    fputs(description, stderr);
}

// TODO: add doc.
static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                  int mods) {

    printf("This is the mouse button callback\n");
}

