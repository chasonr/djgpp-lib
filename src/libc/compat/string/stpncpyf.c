/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *
__stpncpy_chk(char * restrict s1, const char * restrict s2, size_t n, size_t s1size)
{
    if (s1size != (size_t)(-1) && n > s1size) {
        fputs("stpncpy called with buffer size too small\n", stderr);
        abort();
    }

    return stpncpy(s1, s2, n);
}
