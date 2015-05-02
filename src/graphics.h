#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"

struct GLFWwindow;

struct color {
    double r;
    double g;
    double b;
};

void draw_triangle(struct Vertex vertices[], struct color *col);
void draw_line(struct Vertex vertices[], struct color *col);
void draw_quadrilateral(struct Vertex vertices[], struct color *col);
void draw_point(struct Vertex vert);
void translate_object(struct Vertex new_pos);
void rotate_object(double angle);
int get_tri_eq_height_from_side(int side);
struct GLFWwindow* init_window(const int window_length, const int window_height);
void draw_window(struct GLFWwindow *window);
void commit_window(struct GLFWwindow *window);

#endif // ~GRAPHICS_H

