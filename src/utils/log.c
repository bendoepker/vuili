#include "log.h"
#include <stdarg.h>
#include <stdio.h>

void __log(const char* s, ...) {
    va_list ap;
    va_start(ap, s);
    vfprintf(stderr, s, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    fflush(stderr);
}

void __print(const char* s, ...) {
    va_list ap;
    va_start(ap, s);
    vfprintf(stdout, s, ap);
    va_end(ap);
    fprintf(stdout, "\n");
    fflush(stdout);
}
