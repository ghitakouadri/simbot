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

// TODO: remove this rubbish. This is required to compile nanosleep.
//       If you need it, use a compiler switch.

#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#include "robot.h"
#include "common.h"
#include "controller.h"

// TODO: debug only.
#include "graphics.h"

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

static void init_state() {

    robot.destination.x = 0.0;
    robot.destination.y = 0.0;

    robot.heading = 0.0;
}

void init_robot() {

    init_measures();
    init_bumper();
    init_body();
    init_wheels();
    init_state();
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

static void translate_robot() {

    printf("%s: translate to %f %f\n", __func__, robot.position.x,
                                                 robot.position.y);

    translate_object(robot.position);
}

static void rotate_robot() {

    if(!isnan(robot.heading))
    {
        printf("%s: rotating at angle %f\n", __func__, robot.heading);
        glRotated(robot.heading, 0.0, 0.0, 1.0);
    }
}

// Draw robot at origin.
void draw_robot() {

    translate_robot();
    rotate_robot();

    draw_bumper();
    draw_wheels();
    draw_body();
}

// This method updates the robot's position and heading at each time tick.
static void update_robot_state() {

    printf("%s: robot destination %f %f\n", __func__,
            robot.destination.x, robot.destination.y);

    // TODO: this comparison is broken. See #8.
    if(robot.position.x == robot.destination.x &&
       robot.position.y == robot.destination.y)
    {
        return;
    }

    struct Vertex new_pos = get_new_pos(robot.position, robot.heading);

    robot.position.x = new_pos.x;
    robot.position.y = new_pos.y;

    printf("%s: new position x=%f y=%f\n", __func__, new_pos.x, new_pos.y);

    robot.heading = get_new_angle(robot.position, robot.destination);

    printf("%s: new robot heading %f\n", __func__, robot.heading);
}

// TODO: this loop and the graphics loop need to be synchronized.
//       For each state update the graphics loop need to paint another image.
//       See issue #7.
static void* simbot_loop(void* params) {

    UNUSED(params);

    robot.running = true;

    while(robot.running)
    {
        printf("**************************\n");
        printf("simbot loop\n");

        update_robot_state();

        printf("**************************\n\n\n");

        struct timespec time_tick;
        time_tick.tv_sec = 0;
        time_tick.tv_nsec = 200 * 1000 * 1000;
        nanosleep(&time_tick ,NULL);
    }

    return NULL;
}

void set_robot_destination(struct Vertex dest) {

    robot.destination = dest;
}

void start_simbot() {

    init_robot();

    pthread_t simbot_thread;

    int ret = pthread_create(&simbot_thread, NULL, &simbot_loop, NULL);
    if(ret != 0)
    {
        fprintf(stderr, "%s: error starting simbot, %s\n",
                __func__, strerror(errno));

        exit(EXIT_FAILURE);
    }
}

