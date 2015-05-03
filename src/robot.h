#ifndef ROBOT_H
#define ROBOT_H

struct Vertex;

void set_robot_destination(struct Vertex dest);
void update_robot_state(void);
struct Vertex get_robot_position(void);
double get_robot_heading(void);

#endif // ~ROBOT_H

