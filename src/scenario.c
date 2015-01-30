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

static void draw_axes_directions(double half_x, double half_y) {

    struct color col;
    col.r = 0.0;
    col.g = 0.5;
    col.b = 0.0;

    unsigned int tri_side_px = 20;
    unsigned int half_tri_side_px = tri_side_px /2;

    struct vertex vertices[3];
    vertices[0].x = 0;
    vertices[0].y = half_y;

    vertices[1].x = - (GLdouble)half_tri_side_px;
    vertices[1].y = vertices[2].y =
        half_y - get_tri_eq_height_from_side(tri_side_px);

    vertices[2].x = half_tri_side_px;
    draw_triangle(vertices, &col);

    vertices[0].x = half_x;
    vertices[0].y = 0;
    vertices[1].y = - (GLdouble)half_tri_side_px;
    vertices[1].x = vertices[2].x =
        half_x - get_tri_eq_height_from_side(tri_side_px);

    vertices[2].y = half_tri_side_px;
    draw_triangle(vertices, &col);
}

void draw_2d_cartesian_plane(double plane_length, double plane_height) {

    GLdouble half_x = plane_length / 2;
    GLdouble half_y = plane_height / 2;

    struct color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.5;

    struct vertex line_vertices[2];

    // x axis.
    line_vertices[0].x = -half_x;
    line_vertices[0].y = 0;
    line_vertices[1].x = half_x;
    line_vertices[1].y = 0;
    draw_line(line_vertices, &col);

    // y axis.
    line_vertices[0].x = 0;
    line_vertices[0].y = -half_y;
    line_vertices[1].x = 0;
    line_vertices[1].y = half_y;
    draw_line(line_vertices, &col);

    draw_axes_directions(half_x, half_y);
}

