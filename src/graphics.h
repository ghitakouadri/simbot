#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/gl.h>

struct vertex {
    GLdouble x;
    GLdouble y;
};

struct vertices {
    unsigned long vert_count;
    struct vertex verts[];
};

struct vertices* init_vertices(unsigned int vert_count);

void draw_triangle(struct vertices *vert);
void draw_line(struct vertices *vert);
unsigned int get_tri_height_from_side(unsigned int side);

#endif // ~GRAPHICS_H
