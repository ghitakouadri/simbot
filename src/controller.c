#include <math.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "controller.h"
#include "common.h"
#include "robot.h"

static struct {
    const int max_velocity;
    const int time_tick;
    const double k_d_ang_vel;
    double ang_vel;
    double prev_direction;
} controller = { .max_velocity = 100,
                 // 17ms time tick gives up to 60fps.
                 .time_tick = 17,
                 .k_d_ang_vel = 0.03,
                 .ang_vel = 0,
                 .prev_direction = 0
               };

static double get_rad_from_deg(double deg)
{
    return deg * M_PI / 180;
}

static double get_deg_from_rad(double rad)
{
    return rad * 180 / M_PI;
}

static double get_destination_angle(struct Vertex pos, struct Vertex dest)
{
    // Transform the vector identified by the current position and the
    // destination point into the component form <D - P>. A vector in component
    // form has the initial point at the origin of the axes.
    struct Vertex comp_form;
    comp_form.x = dest.x - pos.x;
    comp_form.y = dest.y - pos.y;

    // Calculate the angle between the vector in component form and the x axis.
    double direction = atan(comp_form.y / comp_form.x);
    direction = get_deg_from_rad(direction);

    // In order to calculate the angle between the x axis and the actual
    // destination, the direction needs to be adjusted if the component form is
    // in the second or third quadrant.
    if(comp_form.x < 0)
    {
        direction += 180;
    }

    printf("%s: destination angle %f\n", __func__, direction);

    return direction;
}

/**
 * The angular velocity (omega) model is a simple P regulator.
 */
static double get_direction_delta(struct Vertex pos, struct Vertex dest)
{
    double error = get_destination_angle(pos, dest) - controller.prev_direction;
    printf("angle error: %f\n", error);

    error = get_rad_from_deg(error);

    // P regulator: omega = kp * error
    double direction_delta = controller.k_d_ang_vel * atan2(sin(error), cos(error));

    direction_delta = get_deg_from_rad(direction_delta);
    printf("angular vel %f\n", direction_delta);

    return direction_delta;
}

double get_new_angle(struct Vertex pos, struct Vertex dest)
{
    return controller.prev_direction + get_direction_delta(pos, dest);
}

void sleep_up_to_timetick(struct timespec *elapsed_time)
{
    long sleep_time = controller.time_tick * 1000 - elapsed_time->tv_nsec / 1000;
    if(sleep_time > 0)
    {
        printf("Cycle usleep %ld\n", sleep_time);
        usleep((unsigned int)sleep_time);
    }
}

static double get_current_velocity(struct Vertex current_pos)
{
    static const int PROXIMITY_THRESHOLD = 30;

    // If the robot is close to the goal, reduce speed by 50%.
    struct Vertex dest = get_robot_destination();
    if(fabs(dest.x - current_pos.x) < PROXIMITY_THRESHOLD
       && fabs(dest.y - current_pos.y) < PROXIMITY_THRESHOLD)
    {
        return controller.max_velocity * 0.5;
    }

    return controller.max_velocity;
}

struct Vertex get_new_position(struct Vertex pos, double heading)
{
    heading = get_rad_from_deg(heading);

    static const double one_millis = 1000;
    const double tick_per_sec = one_millis / controller.time_tick;

    const double current_velocity = get_current_velocity(pos);

    struct Vertex new_pos;
    new_pos.x = pos.x + current_velocity / tick_per_sec * cos(heading);

    printf("delta x %f\n", current_velocity / tick_per_sec * cos(heading));

    new_pos.y = pos.y + current_velocity / tick_per_sec * sin(heading);

    printf("delta y %f\n", controller.max_velocity / tick_per_sec * sin(heading));

    controller.prev_direction = get_deg_from_rad(heading);

    return new_pos;
}

