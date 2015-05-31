#ifndef COMMON_H
#define COMMON_H

#include <time.h>
#include <stdbool.h>

#define UNUSED(x) (void)x

struct Vertex {
    double x;
    double y;
};

struct timespec get_elapsed_time(struct timespec start, struct timespec stop);

#endif // ~COMMON_H

