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

#include <stdlib.h>

#include "robot.h"

// TODO: remove magic numbers.
static void draw_bumper() {

    struct vertices *vert_bumper= init_vertices(3);

    vert_bumper->verts[0].x = 0;
    // Half robot height + tri height
    vert_bumper->verts[0].y = 10 + 10;
    vert_bumper->verts[1].x = 10;
    // Robot height
    vert_bumper->verts[1].y = 15;
    vert_bumper->verts[2].x = -10;
    vert_bumper->verts[2].y = 15;

    struct color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.0;
    draw_triangle(vert_bumper, &col);

    free(vert_bumper);
}

static void draw_body() {

    struct vertices *vert_body= init_vertices(4);

    vert_body->verts[0].x = -10;
    vert_body->verts[0].y = 15;
    vert_body->verts[1].x = 10;
    vert_body->verts[1].y = 15;
    vert_body->verts[2].x = 10;
    vert_body->verts[2].y = -15;
    vert_body->verts[3].x = -10;
    vert_body->verts[3].y = -15;

    struct color col;
    col.r = 1.0;
    col.g = 0.0;
    col.b = 0.0;

    draw_quadrilateral(vert_body, &col);

    free(vert_body);
}

static void draw_wheels() {

    struct vertices *vert_wheels = init_vertices(4);

    vert_wheels->verts[0].x = -10 - 5;
    vert_wheels->verts[0].y = -15 + 10;
    vert_wheels->verts[1].x = 10 + 5;
    vert_wheels->verts[1].y = -15 + 10;
    vert_wheels->verts[2].x = 10 + 5;
    vert_wheels->verts[2].y = -15 + 10 - 8;
    vert_wheels->verts[3].x = -10 - 5;
    vert_wheels->verts[3].y = -15 + 10 - 8;

    struct color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.0;

    draw_quadrilateral(vert_wheels, &col);

    free(vert_wheels);
}

// Draw robot at origin.
void robot_draw() {

    draw_bumper();
    draw_wheels();
    draw_body();
}

