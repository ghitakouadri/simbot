#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#include "scenario.h"
#include "graphics.h"

static struct Vertex x_axis_vert[2];
static struct Vertex y_axis_vert[2];
static struct Vertex x_axis_direction_vert[3];
static struct Vertex y_axis_direction_vert[3];

static void draw_axes()
{
    struct color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.5;

    draw_line(x_axis_vert, &col);
    draw_line(y_axis_vert, &col);
}

static void draw_axes_directions()
{
    struct color col;
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

void set_plane_size(double length, double height)
{
    set_axes_vertices(length, height);
    set_axes_direction_vertices(length, height);
}

void draw_2d_cartesian_plane()
{
    draw_axes();
    draw_axes_directions();
}

