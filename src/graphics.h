#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/gl.h>

struct Vertex {
    double x;
    double y;
};

struct color {
    double r;
    double g;
    double b;
};

void draw_triangle(struct Vertex vertices[], struct color *col);
void draw_line(struct Vertex vertices[], struct color *col);
void draw_quadrilateral(struct Vertex vertices[], struct color *col);
void draw_point(struct Vertex vert);
int get_tri_eq_height_from_side(int side);

#endif // ~GRAPHICS_H

