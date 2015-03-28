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
#include <GLFW/glfw3.h>

#include "graphics.h"
#include "scenario.h"

static long round_f_to_l(float x);

// TODO: add doc.
void draw_triangle(struct Vertex vertices[], struct color *col) {

    glBegin(GL_TRIANGLES);
      glColor3d(col->r, col->g, col->b);

      glVertex2d(vertices[0].x, vertices[0].y);
      glVertex2d(vertices[1].x, vertices[1].y);
      glVertex2d(vertices[2].x, vertices[2].y);

    glEnd();
}

// TODO: add doc.
void draw_line(struct Vertex vertices[], struct color *col) {

    glBegin(GL_LINES);
      glColor3d(col->r, col->g, col->b);
      glVertex2d(vertices[0].x, vertices[0].y);
      glVertex2d(vertices[1].x, vertices[1].y);
    glEnd();
}

// TODO: add doc.
void draw_quadrilateral(struct Vertex vertices[], struct color *col) {

    glBegin(GL_QUADS);
      glColor3d(col->r, col->g, col->b);
      glVertex2d(vertices[0].x, vertices[0].y);
      glVertex2d(vertices[1].x, vertices[1].y);
      glVertex2d(vertices[2].x, vertices[2].y);
      glVertex2d(vertices[3].x, vertices[3].y);
    glEnd();
}

void draw_point(struct Vertex vert) {

    glPointSize(20.0);
    glBegin(GL_POINTS);
      glColor3d(1.0, 0.0, 0.0);
      glVertex2d(vert.x, vert.y);
    glEnd();
}

void translate_object(struct Vertex pos) {

    glTranslated(pos.x, pos.y, 0.0);
}

void rotate_object(double angle) {

    glRotated(angle, 0.0, 0.0, 1.0);
}

// TODO: add doc.
int get_tri_eq_height_from_side(int side) {
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
static long round_f_to_l(float x) {
    x += 0.5;
    assert(x >= LONG_MIN && x <= LONG_MAX && "Rounding overflow.\n");

    return (long)x;
}

