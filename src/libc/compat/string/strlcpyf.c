/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t
__strlcpy_chk(char * restrict dest, const char * restrict src, size_t size, size_t destsize)
{
    if (destsize != (size_t)(-1) && size != 0) {
        const char *p1 = memchr(src, '\0', size);
        size_t slen = p1 ? (size_t)(p1 - src + 1) : size;
        if (slen > destsize) {
            fputs("strlcpy called with buffer size too small\n", stderr);
            abort();
        }
    }

    return strlcpy(dest, src, size);
}
