#ifndef GRAPHICS_H
#define GRAPHICS_H

struct vertex {
    int x;
    int y;
};

struct vertices {
    unsigned int vert_count;
    struct vertex verts[];
};

struct vertices* init_vertices(unsigned int vert_count);

void draw_triangle(unsigned int side_px, struct vertices *vert);
unsigned int get_tri_height_from_side(unsigned int side);

#endif // ~GRAPHICS_H
