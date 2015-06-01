#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

#include "scenario.h"
#include "graphics.h"
#include "robot.h"

static struct Vertex x_axis_vert[2];
static struct Vertex y_axis_vert[2];
static struct Vertex x_axis_direction_vert[3];
static struct Vertex y_axis_direction_vert[3];

static struct
{
    const double BODY_LENGTH;
    const double BODY_WIDTH;
    const double BUMPER_HEIGHT;
    const double WHEEL_BODY_OFFSET;
    const double WHEEL_WIDTH;
    const double WHEEL_LENGTH;

    struct Vertex vert_bumper[3];
    struct Vertex vert_body[4];
    struct Vertex vert_wheels[4];

} robot_measures = { .BODY_LENGTH = 30,
                     .BODY_WIDTH = 20,
                     .BUMPER_HEIGHT = 10,
                     .WHEEL_BODY_OFFSET = 5,
                     .WHEEL_WIDTH = 4,
                     .WHEEL_LENGTH = 6
                   };

static struct
{
    const int window_length;
    const int window_height;
    struct Vertex cursor_position;
    GLFWwindow *main_window;
} window_state = { .window_length = 800,
                   .window_height = 800,
                   .cursor_position.x = 0.0,
                   .cursor_position.y = 0.0,
                   .main_window = NULL
                 };

static void draw_axes()
{
    struct Color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.5;

    draw_line(x_axis_vert, &col);
    draw_line(y_axis_vert, &col);
}

static void draw_axes_directions()
{
    struct Color col;
    col.r = 0.0;
    col.g = 0.5;
    col.b = 0.0;

    draw_triangle(x_axis_direction_vert, &col);
    draw_triangle(y_axis_direction_vert, &col);
}

static void set_axes_vertices(double plane_length, double plane_height)
{
    double half_x = plane_length / 2;
    double half_y = plane_height / 2;

    // x axis.
    x_axis_vert[0].x = -half_x;
    x_axis_vert[0].y = 0;
    x_axis_vert[1].x = half_x;
    x_axis_vert[1].y = 0;

    // y axis.
    y_axis_vert[0].x = 0;
    y_axis_vert[0].y = -half_y;
    y_axis_vert[1].x = 0;
    y_axis_vert[1].y = half_y;
}

static void set_axes_direction_vertices(double plane_length,
                                        double plane_height)
{
    double half_x = plane_length / 2;
    double half_y = plane_height / 2;
    int tri_side_px = 20;
    int half_tri_side_px = tri_side_px / 2;

    x_axis_direction_vert[0].x = half_x;
    x_axis_direction_vert[0].y = 0;

    x_axis_direction_vert[1].x = half_x
        - get_tri_eq_height_from_side(tri_side_px);

    x_axis_direction_vert[1].y = - half_tri_side_px;

    x_axis_direction_vert[2].x = x_axis_direction_vert[1].x;
    x_axis_direction_vert[2].y = half_tri_side_px;

    y_axis_direction_vert[0].x = 0;
    y_axis_direction_vert[0].y = half_y;

    y_axis_direction_vert[1].x = - half_tri_side_px;
    y_axis_direction_vert[1].y = half_y
        - get_tri_eq_height_from_side(tri_side_px);

    y_axis_direction_vert[2].x = half_tri_side_px;
    y_axis_direction_vert[2].y = y_axis_direction_vert[1].y;
}

static void init_bumper()
{
    robot_measures.vert_bumper[0].x = robot_measures.BODY_LENGTH / 2;
    robot_measures.vert_bumper[0].y = robot_measures.BODY_WIDTH / 2;
    robot_measures.vert_bumper[1].x = robot_measures.BODY_LENGTH / 2 + robot_measures.BUMPER_HEIGHT;
    robot_measures.vert_bumper[1].y = 0;
    robot_measures.vert_bumper[2].x = robot_measures.BODY_LENGTH / 2;
    robot_measures.vert_bumper[2].y = - robot_measures.BODY_WIDTH / 2;
}

static void init_body()
{
    robot_measures.vert_body[0].x = - robot_measures.BODY_LENGTH / 2;
    robot_measures.vert_body[0].y = robot_measures.BODY_WIDTH / 2;
    robot_measures.vert_body[1].x = robot_measures.BODY_LENGTH / 2;
    robot_measures.vert_body[1].y = robot_measures.BODY_WIDTH / 2;
    robot_measures.vert_body[2].x = robot_measures.BODY_LENGTH / 2;
    robot_measures.vert_body[2].y = - robot_measures.BODY_WIDTH / 2;
    robot_measures.vert_body[3].x = - robot_measures.BODY_LENGTH / 2;
    robot_measures.vert_body[3].y = - robot_measures.BODY_WIDTH / 2;
}

static void init_wheels()
{
    robot_measures.vert_wheels[0].x = - robot_measures.BODY_LENGTH / 2 + robot_measures.WHEEL_BODY_OFFSET;
    robot_measures.vert_wheels[0].y = robot_measures.BODY_WIDTH / 2 + robot_measures.WHEEL_WIDTH;
    robot_measures.vert_wheels[1].x = - robot_measures.BODY_LENGTH / 2 + robot_measures.WHEEL_BODY_OFFSET +
        robot_measures.WHEEL_LENGTH;

    robot_measures.vert_wheels[1].y = robot_measures.BODY_WIDTH / 2 + robot_measures.WHEEL_WIDTH;
    robot_measures.vert_wheels[2].x = - robot_measures.BODY_LENGTH / 2 + robot_measures.WHEEL_BODY_OFFSET +
        robot_measures.WHEEL_LENGTH;

    robot_measures.vert_wheels[2].y = - robot_measures.BODY_WIDTH / 2 - robot_measures.WHEEL_WIDTH;
    robot_measures.vert_wheels[3].x = - robot_measures.BODY_LENGTH / 2 + robot_measures.WHEEL_BODY_OFFSET;
    robot_measures.vert_wheels[3].y = - robot_measures.BODY_WIDTH / 2 - robot_measures.WHEEL_WIDTH;
}

static void draw_bumper()
{
    struct Color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.0;

    draw_triangle(robot_measures.vert_bumper, &col);
}

static void draw_body()
{
    struct Color col;
    col.r = 1.0;
    col.g = 0.0;
    col.b = 0.0;

    draw_quadrilateral(robot_measures.vert_body, &col);
}

static void draw_wheels()
{
    struct Color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.0;

    draw_quadrilateral(robot_measures.vert_wheels, &col);
}

static void translate_robot(struct Vertex position)
{
    printf("%s: translate to %f %f\n", __func__, position.x,
                                                 position.y);

    translate_object(position);
}

static void rotate_robot(double heading)
{
    if(!isnan(heading))
    {
        printf("%s: rotating at angle %f\n", __func__, heading);
        rotate_object(heading);
    }
}

static void draw_2d_cartesian_plane()
{
    draw_axes();
    draw_axes_directions();
}

static void window_size_callback(GLFWwindow *window, int length, int height)
{
    UNUSED(window);
    set_plane_size(length, height);
}

static void error_callback(int err_code, const char* description)
{
    UNUSED(err_code);
    fputs(description, stderr);
}

static void window_to_cartesian_coord(double *x, double *y)
{
    *x = *x - window_state.window_length / 2;

    // The y coordinate is flipped because the window y coordinate grows towards
    // decreasing cartesian y values.
    *y = -(*y - window_state.window_height / 2);
}

static void mouse_position_callback(GLFWwindow *window, double x, double y)
{
    UNUSED(window);
    window_state.cursor_position.x = x;
    window_state.cursor_position.y = y;
}

static struct Vertex get_cursor_position()
{
    double x = window_state.cursor_position.x;
    double y = window_state.cursor_position.y;

    window_to_cartesian_coord(&x, &y);

    struct Vertex cursor_pos = {x, y};

    printf("%s: Recorded destination: x=%f y=%f\n", __func__, x, y );

    return cursor_pos;
}

static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                  int mods)
{
    UNUSED(window);
    UNUSED(button);
    UNUSED(mods);

    if(action == GLFW_PRESS)
    {
        struct Vertex cursor_pos = get_cursor_position();
        set_robot_destination(cursor_pos);
    }
}

static void set_callbacks(GLFWwindow *window)
{
    glfwSetErrorCallback(error_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_position_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
}

void init_robot()
{
    init_bumper();
    init_body();
    init_wheels();
}

void draw_robot(struct Vertex position, double heading)
{
    translate_robot(position);
    rotate_robot(heading);

    draw_bumper();
    draw_wheels();
    draw_body();
}

void set_plane_size(double length, double height)
{
    set_axes_vertices(length, height);
    set_axes_direction_vertices(length, height);
}

void draw_window()
{
    prepare_to_draw_window(window_state.main_window);
    draw_2d_cartesian_plane();
}

void init_scenario()
{
    if(glfwInit() != GL_TRUE)
    {
        exit(EXIT_FAILURE);
    }

    window_state.main_window = glfwCreateWindow(window_state.window_length,
                                                window_state.window_height,
                                                "SimBot", NULL, NULL);

    if(!window_state.main_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_state.main_window);

    set_callbacks(window_state.main_window);
}

void commit_window()
{
    glFlush();
    glfwSwapBuffers(window_state.main_window);
}

bool is_window_open()
{
    return glfwWindowShouldClose(window_state.main_window) == GL_FALSE;
}

void process_events()
{
    glfwPollEvents();
}

void terminate_window()
{
    glfwTerminate();
}

