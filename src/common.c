#include "common.h"

struct timespec get_elapsed_time(struct timespec start, struct timespec stop)
{
    struct timespec elapsed_time;

    if(stop.tv_nsec >= start.tv_nsec)
    {
        elapsed_time.tv_sec = stop.tv_sec - start.tv_sec;
        elapsed_time.tv_nsec = stop.tv_nsec - start.tv_nsec;
    }
    else
    {
        long nanosec = 1000000000;
        elapsed_time.tv_sec = stop.tv_sec - start.tv_sec - 1;
        elapsed_time.tv_nsec = nanosec - start.tv_nsec + stop.tv_nsec;
    }

    return elapsed_time;
}

