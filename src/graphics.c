#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <GLFW/glfw3.h>

#include "graphics.h"
#include "scenario.h"

static long round_f_to_l(float x);

void commit_window(GLFWwindow *window)
{
    glFlush();
    glfwSwapBuffers(window);
}

static void prepare_to_draw_window(GLFWwindow *window)
{
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

void draw_window(GLFWwindow *window)
{
    prepare_to_draw_window(window);
    draw_2d_cartesian_plane();
}

struct GLFWwindow* init_window(const int window_length, const int window_height)
{
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

    return main_window;
}

// TODO: add doc.
void draw_triangle(struct Vertex vertices[], struct color *col)
{
    glBegin(GL_TRIANGLES);
      glColor3d(col->r, col->g, col->b);

      glVertex2d(vertices[0].x, vertices[0].y);
      glVertex2d(vertices[1].x, vertices[1].y);
      glVertex2d(vertices[2].x, vertices[2].y);

    glEnd();
}

// TODO: add doc.
void draw_line(struct Vertex vertices[], struct color *col)
{
    glBegin(GL_LINES);
      glColor3d(col->r, col->g, col->b);
      glVertex2d(vertices[0].x, vertices[0].y);
      glVertex2d(vertices[1].x, vertices[1].y);
    glEnd();
}

// TODO: add doc.
void draw_quadrilateral(struct Vertex vertices[], struct color *col)
{
    glBegin(GL_QUADS);
      glColor3d(col->r, col->g, col->b);
      glVertex2d(vertices[0].x, vertices[0].y);
      glVertex2d(vertices[1].x, vertices[1].y);
      glVertex2d(vertices[2].x, vertices[2].y);
      glVertex2d(vertices[3].x, vertices[3].y);
    glEnd();
}

void draw_point(struct Vertex vert)
{
    glPointSize(20.0);
    glBegin(GL_POINTS);
      glColor3d(1.0, 0.0, 0.0);
      glVertex2d(vert.x, vert.y);
    glEnd();
}

void translate_object(struct Vertex pos)
{
    glTranslated(pos.x, pos.y, 0.0);
}

void rotate_object(double angle)
{
    glRotated(angle, 0.0, 0.0, 1.0);
}

// TODO: add doc.
int get_tri_eq_height_from_side(int side)
{
    assert(side > 0 && "The size of the side must be > 0.\n");

    // For equilateral triangle:
    // h^2 = side^2 - (size/2)^2
    float h_square = powf(side, 2) - powf(round_f_to_l(side/2.0f), 2);

    float h = sqrtf(h_square);

    assert(h >= INT_MIN && h <= INT_MAX &&
            "Undefined float to integer conversion");

    return (int) h;
}

// TODO: add doc.
static long round_f_to_l(float x)
{
    x += 0.5;
    assert(x >= LONG_MIN && x <= LONG_MAX && "Rounding overflow.\n");

    return (long)x;
}

