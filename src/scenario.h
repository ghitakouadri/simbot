#ifndef SCENARIO_H
#define SCENARIO_H

#include <stdbool.h>

struct GLFWwindow;
struct Vertex;

void draw_window(void);
void set_plane_size(double plane_length, double plane_height);
void init_robot(void);
void draw_robot(struct Vertex position, double heading);
void init_scenario(void);
void commit_window(void);
bool is_window_open(void);
void process_events(void);
void terminate_window(void);

#endif // ~SCENARIO_H

