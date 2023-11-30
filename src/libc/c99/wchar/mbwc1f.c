/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

size_t
__mbsrtowcs_chk(wchar_t * restrict dst, const char ** restrict src, size_t len, mbstate_t * restrict ps, size_t dstsize)
{
    if (dst != NULL && dstsize != (size_t)(-1) && dstsize < len) {
        fputs("mbsrtowcs called with buffer size too small\n", stderr);
        abort();
    }

    return mbsrtowcs(dst, src, len, ps);
}
