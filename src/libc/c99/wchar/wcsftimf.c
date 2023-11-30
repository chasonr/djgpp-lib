/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

size_t
__wcsftime_chk(wchar_t * restrict s, size_t maxsize, const wchar_t * restrict format, const struct tm * restrict timeptr, size_t ssize)
{
    if (ssize != (size_t)(-1) && maxsize > ssize) {
        /* Call with the lesser size and fail if the buffer fills up */
        size_t n2 = wcsftime(s, ssize, format, timeptr);
        if (n2 == 0) {
            fputs("wcsftime called with buffer size too small\n", stderr);
            abort();
        }
        return n2;
    }

    return wcsftime(s, maxsize, format, timeptr);
}
