/*
    simbot is a simulator of a 2 wheels differential drive robot.
    Copyright (C) 2014 Roberto Cometti <modsrm@pagefault.io>

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
#include <GLFW/glfw3.h>

#include "graphics.h"

static long round_f_to_l(float x);

// TODO: add doc.
void draw_triangle(struct vertices *vert, struct color *col) {

    assert(vert->vert_count == 3 && "There should be 3 vertices.\n");

    glBegin(GL_TRIANGLES);
      glColor3d(col->r, col->g, col->b);

      glVertex2d(vert->verts[0].x, vert->verts[0].y);
      glVertex2d(vert->verts[1].x, vert->verts[1].y);
      glVertex2d(vert->verts[2].x, vert->verts[2].y);

    glEnd();
}

// TODO: add doc.
void draw_line(struct vertices *vert, struct color *col) {

    assert(vert->vert_count == 2 && "There should be 2 vertices.\n");

    glBegin(GL_LINES);
      glColor3d(col->r, col->g, col->b);
      glVertex2d(vert->verts[0].x, vert->verts[0].y);
      glVertex2d(vert->verts[1].x, vert->verts[1].y);
    glEnd();
}

// TODO: add doc.
void draw_quadrilateral(struct vertices *vert, struct color *col) {

    assert(vert->vert_count == 4 && "There should be 4 vertices.\n");

    glBegin(GL_QUADS);
      glColor3d(col->r, col->g, col->b);
      glVertex2d(vert->verts[0].x, vert->verts[0].y);
      glVertex2d(vert->verts[1].x, vert->verts[1].y);
      glVertex2d(vert->verts[2].x, vert->verts[2].y);
      glVertex2d(vert->verts[3].x, vert->verts[3].y);
    glEnd();
}

// TODO: add doc.
static unsigned int get_tri_eq_height_from_side(unsigned int side) {
    assert(side > 0 && "The size of the side must be > 0.\n");

    // For equilateral triangle:
    // h^2 = side^2 - (size/2)^2
    float h_square = powf(side, 2) - powf(round_f_to_l(side/2.0f), 2);

    float h = sqrtf(h_square);

    assert(h >= INT_MIN && h <= INT_MAX &&
            "Undefined float to integer conversion");

    return (unsigned int)h;
}

static void draw_axes_directions(GLdouble half_x, GLdouble half_y) {

    struct color col;
    col.r = 0.0;
    col.g = 0.5;
    col.b = 0.0;

    unsigned int tri_side_px = 20;
    unsigned int half_tri_side_px = tri_side_px /2;

    struct vertices *vert = init_vertices(3);
    vert->verts[0].x = 0;
    vert->verts[0].y = half_y;

    vert->verts[1].x = - (GLdouble)half_tri_side_px;
    vert->verts[1].y = vert->verts[2].y =
        half_y - get_tri_eq_height_from_side(tri_side_px);

    vert->verts[2].x = half_tri_side_px;
    draw_triangle(vert, &col);

    vert->verts[0].x = half_x;
    vert->verts[0].y = 0;
    vert->verts[1].y = - (GLdouble)half_tri_side_px;
    vert->verts[1].x = vert->verts[2].x =
        half_x - get_tri_eq_height_from_side(tri_side_px);

    vert->verts[2].y = half_tri_side_px;
    draw_triangle(vert, &col);

    free(vert);
}

void draw_2d_cartesian_plane(double plane_length, double plane_height) {

    GLdouble half_x = plane_length / 2;
    GLdouble half_y = plane_height / 2;

    struct color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.5;

    struct vertices *line_vert = init_vertices(2);

    // x axis.
    line_vert->verts[0].x = -half_x;
    line_vert->verts[0].y = 0;
    line_vert->verts[1].x = half_x;
    line_vert->verts[1].y = 0;
    draw_line(line_vert, &col);

    // y axis.
    line_vert->verts[0].x = 0;
    line_vert->verts[0].y = -half_y;
    line_vert->verts[1].x = 0;
    line_vert->verts[1].y = half_y;
    draw_line(line_vert, &col);

    free(line_vert);

    draw_axes_directions(half_x, half_y);
}

// TODO: add doc.
struct vertices* init_vertices(unsigned int vert_count) {

    struct vertices *vert = malloc( sizeof(struct vertices) +
            vert_count * sizeof(struct vertex) );

    vert->vert_count = vert_count;
    return vert;
}

// TODO: add doc.
static long round_f_to_l(float x) {
    x += 0.5;
    assert(x >= LONG_MIN && x <= LONG_MAX && "Rounding overflow.\n");

    return (long)x;
}

