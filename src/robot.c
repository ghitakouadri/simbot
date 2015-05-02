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
void update_robot_state() {

    printf("RSU BEGIN:\n");
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
    printf("RSU END:\n\n");
}

void set_robot_destination(struct Vertex dest) {

    robot.destination = dest;
}

