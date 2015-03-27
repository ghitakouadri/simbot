#ifndef SIMBOT_H
#define SIMBOT_H

#include <stdbool.h>

#include "graphics.h"

struct simbot {

    const int window_length;
    const int window_height;
    struct Vertex destination;
    struct Vertex position;
    volatile bool running;

    double heading;
};

extern struct simbot simbot_prog;

#endif // ~SIMBOT_H
