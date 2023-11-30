/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

wchar_t *
__wmemmove_chk(wchar_t *s1, const wchar_t *s2, size_t n, size_t s1size)
{
    if (s1size != (size_t)(-1) && s1size < n) {
        fputs("wmemmove called with buffer size too small\n", stderr);
        abort();
    }

    return wmemmove(s1, s2, n);
}
