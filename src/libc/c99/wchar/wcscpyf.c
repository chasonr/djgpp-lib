/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

wchar_t *
__wcscpy_chk(wchar_t * restrict s1, const wchar_t * restrict s2, size_t s1size)
{
    if (s1size != (size_t)(-1) && wmemchr(s2, L'\0', s1size) == NULL) {
        fputs("wcscpy called with buffer size too small\n", stderr);
        abort();
    }

    return wcscpy(s1, s2);
}
