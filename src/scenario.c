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

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#include "scenario.h"
#include "graphics.h"

static struct vertex x_axis_vert[2];
static struct vertex y_axis_vert[2];
static struct vertex x_axis_direction_vert[3];
static struct vertex y_axis_direction_vert[3];

static void draw_axes() {

    struct color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.5;

    draw_line(x_axis_vert, &col);
    draw_line(y_axis_vert, &col);
}

static void draw_axes_directions() {

    struct color col;
    col.r = 0.0;
    col.g = 0.5;
    col.b = 0.0;

    draw_triangle(x_axis_direction_vert, &col);
    draw_triangle(y_axis_direction_vert, &col);
}

static void set_axes_vertices(double plane_length, double plane_height) {

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
                                        double plane_height) {

    double half_x = plane_length / 2;
    double half_y = plane_height / 2;
    int tri_side_px = 20;
    int half_tri_side_px = tri_side_px / 2;

    x_axis_direction_vert[0].x = 0;
    x_axis_direction_vert[0].y = half_x;

    x_axis_direction_vert[1].x = - half_tri_side_px;
    x_axis_direction_vert[1].y = half_x
        - get_tri_eq_height_from_side(tri_side_px);

    x_axis_direction_vert[2].y = x_axis_direction_vert[1].y;

    x_axis_direction_vert[2].x = half_tri_side_px;

    y_axis_direction_vert[0].x = half_y;
    y_axis_direction_vert[0].y = 0;
    y_axis_direction_vert[1].y = - half_tri_side_px;
    y_axis_direction_vert[1].x = half_y
        - get_tri_eq_height_from_side(tri_side_px);

    y_axis_direction_vert[2].x = y_axis_direction_vert[1].x;

    y_axis_direction_vert[2].y = half_tri_side_px;
}

void set_plane_size(double length, double height) {

    set_axes_vertices(length, height);
    set_axes_direction_vertices(length, height);
}

void draw_2d_cartesian_plane() {

    draw_axes();
    draw_axes_directions();
}

