/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void *
__memmove_chk(void *s1, const void *s2, size_t n, size_t s1size)
{
    if (s1size != (size_t)(-1) && s1size < n) {
        fputs("memmove called with buffer size too small\n", stderr);
        abort();
    }

    return memmove(s1, s2, n);
}
