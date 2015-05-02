#ifndef ROBOT_H
#define ROBOT_H

#include <GLFW/glfw3.h>
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

