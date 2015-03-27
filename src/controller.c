#include <math.h>
#include <stdio.h>

#include "controller.h"
// TODO: decuple the controller from the graphics.
#include "graphics.h"

struct Controller controller;

static double get_destination_angle(struct Vertex pos, struct Vertex dest) {

    // Transform the vector identified by the current position and the
    // destination point into the component form <D - P>. A vector in component
    // form has the initial point at the origin of the axes.
    struct Vertex comp_form;
    comp_form.x = dest.x - pos.x;
    comp_form.y = dest.y - pos.y;

    // Calculate the angle between the vector in component form and the x axis.
    double direction = atan(comp_form.y / comp_form.x) * 180 / 3.14;

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

static double get_ang_vel(struct Vertex pos, struct Vertex dest) {

    double error = get_destination_angle(pos, dest) - controller.prev_direction;
    printf("angle error: %f\n", error);

    // Convert to rad.
    error *= 3.14 / 180;

    double ang_vel = controller.k_d_ang_vel * atan2(sin(error), cos(error));

    // Convert to deg.
    ang_vel *= 180 / 3.14;
    printf("angular vel %f\n", ang_vel);

    return ang_vel;
}

void init_controller() {

    controller.max_velocity = 4;
    controller.time_tick = 200;
    controller.ang_vel = 0;
    controller.k_d_ang_vel = 0.1;
    controller.prev_direction = 0;
}

double get_new_angle(struct Vertex pos, struct Vertex dest) {

    return get_ang_vel(pos, dest) + controller.prev_direction;
}

struct Vertex get_new_pos(struct Vertex pos, double heading) {

    heading *= 3.14 / 180;

    struct Vertex new_pos;
    new_pos.x = pos.x +
        controller.max_velocity * cos(heading);

    printf("delta x %f\n", controller.max_velocity * cos(heading));

    new_pos.y = pos.y +
        controller.max_velocity * sin(heading);

    printf("delta y %f\n", controller.max_velocity * sin(heading));

    controller.prev_direction = heading * 180 / 3.14;

    return new_pos;
}

