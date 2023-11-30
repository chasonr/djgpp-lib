/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int
__wctomb_chk(char *s, wchar_t wchar, size_t ssize)
{
    int len;

    if (ssize != (size_t)(-1) && ssize < MB_LEN_MAX) {
        char s2[MB_LEN_MAX];
        len = wctomb(s2, wchar);
        if (len >= 0 && (unsigned)len > ssize) {
            fputs("wctomb buffer overrun\n", stderr);
            abort();
        }
        if (len >= 0) {
            memcpy(s, s2, len);
        }
    } else {
        len = wctomb(s, wchar);
    }
    return len;
}
