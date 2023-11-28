/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void *
__memset_chk(void *s, int c, size_t n, size_t ssize)
{
    if (ssize != (size_t)(-1) && ssize < n) {
        fputs("memset called with buffer size too small\n", stderr);
        abort();
    }

    return memset(s, c, n);
}
