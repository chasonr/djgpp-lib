/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdlib.h>
#include <stdio.h>

size_t
__mbstowcs_chk(wchar_t * restrict wcs, const char * restrict s, size_t n, size_t wcssize)
{
    if (wcssize != (size_t)(-1) && wcssize < n) {
        fputs("mbstowcs called with buffer size too small\n", stderr);
        abort();
    }

    return mbstowcs(wcs, s, n);
}
