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

void robot_draw(struct robot *rob) {

    struct color col;

    // TODO: move in struct.
    const GLdouble robot_length = 20;
    const GLdouble robot_height = 30;

    // Bumper
    struct vertices *vert_tri = init_vertices(3);

    vert_tri->verts[0].x = rob->pos.x;
    vert_tri->verts[0].y = rob->pos.y;
    vert_tri->verts[1].x = vert_tri->verts[0].x + robot_length / 2;
    vert_tri->verts[1].y = vert_tri->verts[0].x -10;
    vert_tri->verts[2].x = vert_tri->verts[0].x - robot_length / 2;
    vert_tri->verts[2].y = vert_tri->verts[1].y;

    struct vertices *vert_body= init_vertices(4);

    // Body 20x30 px


    vert_body->verts[0].x = vert_tri->verts[2].x;
    vert_body->verts[0].y = vert_tri->verts[2].y;
    vert_body->verts[1].x = vert_tri->verts[1].x;
    vert_body->verts[1].y = vert_tri->verts[1].y;
    vert_body->verts[2].x = vert_body->verts[1].x;
    vert_body->verts[2].y = vert_body->verts[1].y - robot_height;
    vert_body->verts[3].x = vert_body->verts[0].x;
    vert_body->verts[3].y = vert_body->verts[0].y - robot_height;

    // Wheels 30x8
    struct vertices *vert_wheels = init_vertices(4);

    vert_wheels->verts[0].x = vert_body->verts[3].x - 5;
    vert_wheels->verts[0].y = vert_body->verts[3].y + 10;
    vert_wheels->verts[1].x = vert_body->verts[2].x + 5;
    vert_wheels->verts[1].y = vert_body->verts[2].y + 10;
    vert_wheels->verts[2].x = vert_wheels->verts[1].x;
    vert_wheels->verts[2].y = vert_wheels->verts[1].y - 8;
    vert_wheels->verts[3].x = vert_wheels->verts[0].x;
    vert_wheels->verts[3].y = vert_wheels->verts[0].y -8;

    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.0;
    draw_triangle(vert_tri, &col);
    draw_quadrilateral(vert_wheels, &col);

    col.r = 1.0;
    col.g = 0.0;
    col.b = 0.0;
    draw_quadrilateral(vert_body, &col);

    free(vert_body);
    free(vert_wheels);
    free(vert_tri);
}

