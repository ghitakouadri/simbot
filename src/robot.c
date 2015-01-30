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

struct Robot robot;

static void init_measures() {
    robot.BODY_LENGTH = 30;
    robot.BODY_WIDTH = 20;
    robot.BUMPER_HEIGHT = 10;
    robot.WHEEL_BODY_OFFSET = 5;
    robot.WHEEL_WIDTH = 4;
    robot.WHEEL_LENGTH = 6;
}

static void init_bumper() {

    robot.vert_bumper[0].x = robot.BODY_LENGTH / 2;
    robot.vert_bumper[0].y = robot.BODY_WIDTH / 2;
    robot.vert_bumper[1].x = robot.BODY_LENGTH / 2 + robot.BUMPER_HEIGHT;
    robot.vert_bumper[1].y = 0;
    robot.vert_bumper[2].x = robot.BODY_LENGTH / 2;
    robot.vert_bumper[2].y = - robot.BODY_WIDTH / 2;
}

static void init_body() {

    robot.vert_body[0].x = - robot.BODY_LENGTH / 2;
    robot.vert_body[0].y = robot.BODY_WIDTH / 2;
    robot.vert_body[1].x = robot.BODY_LENGTH / 2;
    robot.vert_body[1].y = robot.BODY_WIDTH / 2;
    robot.vert_body[2].x = robot.BODY_LENGTH / 2;
    robot.vert_body[2].y = - robot.BODY_WIDTH / 2;
    robot.vert_body[3].x = - robot.BODY_LENGTH / 2;
    robot.vert_body[3].y = - robot.BODY_WIDTH / 2;
}

static void init_wheels() {

    robot.vert_wheels[0].x = - robot.BODY_LENGTH / 2 + robot.WHEEL_BODY_OFFSET;
    robot.vert_wheels[0].y = robot.BODY_WIDTH / 2 + robot.WHEEL_WIDTH;
    robot.vert_wheels[1].x = - robot.BODY_LENGTH / 2 + robot.WHEEL_BODY_OFFSET +
        robot.WHEEL_LENGTH;

    robot.vert_wheels[1].y = robot.BODY_WIDTH / 2 + robot.WHEEL_WIDTH;
    robot.vert_wheels[2].x = - robot.BODY_LENGTH / 2 + robot.WHEEL_BODY_OFFSET +
        robot.WHEEL_LENGTH;

    robot.vert_wheels[2].y = - robot.BODY_WIDTH / 2 - robot.WHEEL_WIDTH;
    robot.vert_wheels[3].x = - robot.BODY_LENGTH / 2 + robot.WHEEL_BODY_OFFSET;
    robot.vert_wheels[3].y = - robot.BODY_WIDTH / 2 - robot.WHEEL_WIDTH;
}

void init_robot() {

    init_measures();
    init_bumper();
    init_body();
    init_wheels();
}

static void draw_bumper() {

    struct color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.0;

    draw_triangle(robot.vert_bumper, &col);
}

static void draw_body() {

    struct color col;
    col.r = 1.0;
    col.g = 0.0;
    col.b = 0.0;

    draw_quadrilateral(robot.vert_body, &col);
}

static void draw_wheels() {

    struct color col;
    col.r = 0.0;
    col.g = 0.0;
    col.b = 0.0;

    draw_quadrilateral(robot.vert_wheels, &col);
}

// Draw robot at origin.
void draw_robot() {

    draw_bumper();
    draw_wheels();
    draw_body();
}

