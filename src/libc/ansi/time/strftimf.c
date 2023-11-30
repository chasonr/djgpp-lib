/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

size_t
__strftime_chk(char * restrict s, size_t maxsize, const char * restrict format, const struct tm * restrict timeptr, size_t ssize)
{
    if (ssize != (size_t)(-1) && maxsize > ssize) {
        /* Call with the lesser size and fail if the buffer fills up */
        size_t n2 = strftime(s, ssize, format, timeptr);
        if (n2 == 0) {
            fputs("strftime called with buffer size too small\n", stderr);
            abort();
        }
        return n2;
    }

    return strftime(s, maxsize, format, timeptr);
}
