/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

size_t
__wcsrtombs_chk(char * restrict dst, const wchar_t ** restrict src, size_t len, mbstate_t * restrict ps, size_t dstsize)
{
    if (dst != NULL && dstsize != (size_t)(-1) && dstsize < len) {
        fputs("wcsrtombs called with buffer size too small\n", stderr);
        abort();
    }

    return wcsrtombs(dst, src, len, ps);
}
