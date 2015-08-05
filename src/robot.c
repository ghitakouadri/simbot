#include <stdio.h>
#include <math.h>

#include "robot.h"
#include "common.h"
#include "controller.h"

static struct
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

static bool is_at_destination()
{
    double x_delta = robot_state.destination.x - robot_state.position.x;
    double y_delta = robot_state.destination.y - robot_state.position.y;

    static const int DESTINATION_THRESHOLD = 15;

    return fabs(x_delta) < DESTINATION_THRESHOLD
           && fabs(y_delta) < DESTINATION_THRESHOLD ? true : false;
}

/**
 * Updates the robot's position and heading at each time tick.
 */
void update_robot_state()
{
    printf("RSU BEGIN:\n");
    printf("%s: robot destination %f %f\n", __func__,
            robot_state.destination.x, robot_state.destination.y);

    if(is_at_destination())
    {
        return;
    }

    struct Vertex new_pos = get_new_position(robot_state.position,
                                             robot_state.heading);

    robot_state.position.x = new_pos.x;
    robot_state.position.y = new_pos.y;

    printf("%s: new position x=%f y=%f\n", __func__, new_pos.x, new_pos.y);

    robot_state.heading = get_new_angle(robot_state.position,
                                        robot_state.destination);

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

struct Vertex get_robot_destination()
{
    return robot_state.destination;
}

