#include <stdio.h>

#include "log.h"

void log_info(const char *caller, const char *message) {

    printf("%s: %s\n", caller, message);
}

