#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/gl.h>

struct vertex {
    double x;
    double y;
};

struct color {
    double r;
    double g;
    double b;
};

void draw_triangle(struct vertex vertices[], struct color *col);
void draw_line(struct vertex vertices[], struct color *col);
void draw_quadrilateral(struct vertex vertices[], struct color *col);
unsigned int get_tri_height_from_side(unsigned int side);

#endif // ~GRAPHICS_H
