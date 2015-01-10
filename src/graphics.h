#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/gl.h>

struct vertex {
    GLdouble x;
    GLdouble y;
};

struct color {
    GLdouble r;
    GLdouble g;
    GLdouble b;
};

struct vertices {
    unsigned long vert_count;
    struct vertex verts[];
};

// TODO: refactor to avoid malloc and free.
struct vertices* init_vertices(unsigned int vert_count);

void draw_triangle(struct vertices *vert, struct color *col);
void draw_line(struct vertices *vert, struct color *col);
void draw_quadrilateral(struct vertices *vert, struct color *col);
unsigned int get_tri_height_from_side(unsigned int side);
void draw_2d_cartesian_plane(double plane_length, double plane_height);

#endif // ~GRAPHICS_H
