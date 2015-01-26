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

static const GLdouble BODY_LENGTH = 30;
static const GLdouble BODY_WIDTH = 20;
static const GLdouble BUMPER_HEIGHT = 10;
static const GLdouble WHEEL_BODY_OFFSET = 5;
static const GLdouble WHEEL_WIDTH = 4;
static const GLdouble WHEEL_LENGTH = 6;

static void draw_bumper() {

    struct vertices *vert_bumper = init_vertices(3);

    vert_bumper->verts[0].x = BODY_LENGTH / 2;
    vert_bumper->verts[0].y = BODY_WIDTH / 2;
    vert_bumper->verts[1].x = BODY_LENGTH / 2 + BUMPER_HEIGHT;
    vert_bumper->verts[1].y = 0;
    vert_bumper->verts[2].x = BODY_LENGTH / 2;
    vert_bumper->verts[2].y = - BODY_WIDTH / 2;

    struct color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.0;
    draw_triangle(vert_bumper, &col);

    free(vert_bumper);
}

static void draw_body() {

    struct vertices *vert_body= init_vertices(4);

    vert_body->verts[0].x = - BODY_LENGTH / 2;
    vert_body->verts[0].y = BODY_WIDTH / 2;
    vert_body->verts[1].x = BODY_LENGTH / 2;
    vert_body->verts[1].y = BODY_WIDTH / 2;
    vert_body->verts[2].x = BODY_LENGTH / 2;
    vert_body->verts[2].y = - BODY_WIDTH / 2;
    vert_body->verts[3].x = - BODY_LENGTH / 2;
    vert_body->verts[3].y = - BODY_WIDTH / 2;

    struct color col;
    col.r = 1.0;
    col.g = 0.0;
    col.b = 0.0;

    draw_quadrilateral(vert_body, &col);

    free(vert_body);
}

static void draw_wheels() {

    struct vertices *vert_wheels = init_vertices(4);

    vert_wheels->verts[0].x = - BODY_LENGTH / 2 + WHEEL_BODY_OFFSET;
    vert_wheels->verts[0].y = BODY_WIDTH / 2 + WHEEL_WIDTH;
    vert_wheels->verts[1].x = - BODY_LENGTH / 2 + WHEEL_BODY_OFFSET + WHEEL_LENGTH;
    vert_wheels->verts[1].y = BODY_WIDTH / 2 + WHEEL_WIDTH;
    vert_wheels->verts[2].x = - BODY_LENGTH / 2 + WHEEL_BODY_OFFSET + WHEEL_LENGTH;
    vert_wheels->verts[2].y = - BODY_WIDTH / 2 - WHEEL_WIDTH;
    vert_wheels->verts[3].x = - BODY_LENGTH / 2 + WHEEL_BODY_OFFSET;
    vert_wheels->verts[3].y = - BODY_WIDTH / 2 - WHEEL_WIDTH;

    struct color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.0;

    draw_quadrilateral(vert_wheels, &col);

    free(vert_wheels);
}

// Draw robot at origin.
void draw_robot() {

    draw_bumper();
    draw_wheels();
    draw_body();
}

