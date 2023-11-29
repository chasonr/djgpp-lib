/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t
__strxfrm_chk(char * restrict s1, const char * restrict s2, size_t n, size_t s1size)
{
    if (s1size != (size_t)(-1) && n > s1size) {
        /* Call with the lesser size and fail if the buffer fills up */
        size_t n2 = strxfrm(s1, s2, s1size);
        if (n2 >= s1size) {
            fputs("strxfrm called with buffer size too small\n", stderr);
            abort();
        }
        return n2;
    }

    return strxfrm(s1, s2, n);
}
