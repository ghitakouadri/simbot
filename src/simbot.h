#ifndef SIMBOT_H
#define SIMBOT_H

#include <stdbool.h>

#include "graphics.h"

struct Program {

    const int window_length;
    const int window_height;
    volatile bool running;
};

#endif // ~SIMBOT_H
