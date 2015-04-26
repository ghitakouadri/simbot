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

#ifndef ROBOT_H
#define ROBOT_H

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "common.h"

struct Robot {
    GLdouble BODY_LENGTH;
    GLdouble BODY_WIDTH;
    GLdouble BUMPER_HEIGHT;
    GLdouble WHEEL_BODY_OFFSET;
    GLdouble WHEEL_WIDTH;
    GLdouble WHEEL_LENGTH;

    struct Vertex vert_bumper[3];
    struct Vertex vert_body[4];
    struct Vertex vert_wheels[4];

    struct Vertex destination;
    struct Vertex position;

    double heading;
};

extern struct Robot robot;

void init_robot(void);

/**
 * Draws robot at the origin.
 */
void draw_robot(void);

void set_robot_destination(struct Vertex dest);

void update_robot_state(void);

#endif // ~ROBOT_H

