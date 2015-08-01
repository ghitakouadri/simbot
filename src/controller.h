#ifndef CONTROLLER_H
#define CONTROLLER_H

struct Vertex;
struct timespec;

double get_new_angle(struct Vertex pos, struct Vertex dest);
struct Vertex get_new_position(struct Vertex pos, double heading);

/**
 * Sleeps up to the time tick.
 * If the provided elapsed time is shorter than the time tick,
 * sleeps for time tick - elapsed time.
 *
 * @param[in] elapsed_time the time used to check against the time tick.
 */
void sleep_up_to_timetick(struct timespec *elapsed_time);

#endif // ~CONTROLLER_H

