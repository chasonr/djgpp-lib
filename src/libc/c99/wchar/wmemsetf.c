/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

wchar_t *
__wmemset_chk(wchar_t *s, wchar_t c, size_t n, size_t ssize)
{
    if (ssize != (size_t)(-1) && ssize < n) {
        fputs("wmemset called with buffer size too small\n", stderr);
        abort();
    }

    return wmemset(s, c, n);
}
