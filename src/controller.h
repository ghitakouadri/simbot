#ifndef CONTROLLER_H
#define CONTROLLER_H

struct Vertex;

// TODO: audit variables' placement.
struct Controller {
    double max_velocity;
    int time_tick;
    double ang_vel;
    double k_d_ang_vel;
    double prev_direction;
};

extern struct Controller controller;

void init_controller(void);
double get_new_angle(struct Vertex pos, struct Vertex dest);
struct Vertex get_new_pos(struct Vertex pos, double heading);
void bound_frame_time(struct timespec *elapsed_time);

#endif // ~CONTROLLER_H

