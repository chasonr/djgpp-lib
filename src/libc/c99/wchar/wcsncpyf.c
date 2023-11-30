/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

wchar_t *
__wcsncpy_chk(wchar_t * restrict s1, const wchar_t * restrict s2, size_t n, size_t s1size)
{
    if (s1size != (size_t)(-1) && n > s1size) {
        fputs("wcsncpy called with buffer size too small\n", stderr);
        abort();
    }

    return wcsncpy(s1, s2, n);
}
