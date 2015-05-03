#ifndef SCENARIO_H
#define SCENARIO_H

struct GLFWwindow;
struct Vertex;

void draw_window(struct GLFWwindow *window);
void set_plane_size(double plane_length, double plane_height);
void init_robot(void);
void draw_robot(struct Vertex position, double heading);

#endif // ~SCENARIO_H

