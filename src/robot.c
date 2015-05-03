#include <stdio.h>

#include "robot.h"
#include "common.h"
#include "controller.h"

static struct Robot
{
    struct Vertex destination;
    struct Vertex position;

    double heading;
} robot_state = { .destination.x = 0.0,
                  .destination.y = 0.0,
                  .position.x = 0.0,
                  .position.y = 0.0,
                  .heading = 0.0
                };

// This method updates the robot's position and heading at each time tick.
void update_robot_state()
{
    printf("RSU BEGIN:\n");
    printf("%s: robot destination %f %f\n", __func__,
            robot_state.destination.x, robot_state.destination.y);

    // TODO: this comparison is broken. See #8.
    if(robot_state.position.x == robot_state.destination.x &&
       robot_state.position.y == robot_state.destination.y)
    {
        return;
    }

    struct Vertex new_pos = get_new_pos(robot_state.position, robot_state.heading);

    robot_state.position.x = new_pos.x;
    robot_state.position.y = new_pos.y;

    printf("%s: new position x=%f y=%f\n", __func__, new_pos.x, new_pos.y);

    robot_state.heading = get_new_angle(robot_state.position, robot_state.destination);

    printf("%s: new robot_state heading %f\n", __func__, robot_state.heading);
    printf("RSU END:\n\n");
}

void set_robot_destination(struct Vertex dest)
{
    robot_state.destination = dest;
}

struct Vertex get_robot_position()
{
    return robot_state.position;
}

double get_robot_heading()
{
    return robot_state.heading;
}

