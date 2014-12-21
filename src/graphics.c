#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <GLFW/glfw3.h>

#include "graphics.h"

static long round_f_to_l(float x);

void draw_triangle(unsigned int side_px, struct vertices *vert) {

    assert(vert->vert_count == 3 && "There should be 3 vertices.\n");

    glBegin(GL_TRIANGLES);
      glColor3f(0.0, 0.5, 0.0);

      glVertex2s(vert->verts[0].x, vert->verts[0].y);
      glVertex2s(vert->verts[1].x, vert->verts[1].y);
      glVertex2s(vert->verts[2].x, vert->verts[2].y);

    glEnd();
}

void draw_line(struct vertices *vert) {

    assert(vert->vert_count == 2 && "There should be 2 vertices.\n");

    glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);
      glVertex2s(vert->verts[0].x, vert->verts[0].y);
      glVertex2s(vert->verts[1].x, vert->verts[1].y);
    glEnd();
}

// TODO: add doc.
unsigned int get_tri_height_from_side(unsigned int side) {
    assert(side > 0 && "The size of the side must be > 0.\n");

    // For equilateral triangle:
    // h^2 = side^2 - (size/2)^2
    float h_square = pow(side, 2) - powf(round_f_to_l(side/2.0), 2);

    float h = sqrtf(h_square);

    assert(h >= INT_MIN && h <= INT_MAX &&
            "Undefined float to integer conversion");

    return (unsigned int)h;
}

// TODO: add doc.
struct vertices* init_vertices(unsigned int vert_count) {

    struct vertices *vert = malloc( sizeof(struct vertices) +
            vert_count * sizeof(struct vertex) );

    vert->vert_count = vert_count;
    return vert;
}

// TODO: add doc.
static long round_f_to_l(float x) {
    x += 0.5;
    assert(x >= LONG_MIN && x <= LONG_MAX && "Rounding overflow.\n");

    return (long)x;
}

