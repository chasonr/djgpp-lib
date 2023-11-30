/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdlib.h>
#include <stdio.h>

size_t
__wcstombs_chk(char * restrict s, const wchar_t * restrict wcs, size_t n, size_t ssize)
{
    if (ssize != (size_t)(-1) && ssize < n) {
        fputs("wcstombs called with buffer size too small\n", stderr);
        abort();
    }

    return wcstombs(s, wcs, n);
}
