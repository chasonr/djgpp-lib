/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void *
__memccpy_chk(void * restrict to, const void * restrict from, int c, size_t n, size_t tosize)
{
    if (tosize != (size_t)(-1)) {
        const void *p = memchr(from, c, n);
        size_t len = p ? (size_t)((const char *)p - (const char *)from + 1) : n;
        if (len > tosize) {
            fputs("memccpy called with buffer size too small\n", stderr);
            abort();
        }
    }

    return memccpy(to, from, c, n);
}
