/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

size_t
__wcrtomb_chk(char * restrict s, wchar_t wc, mbstate_t * restrict ps, size_t ssize)
{
    if (s != NULL && ssize != (size_t)(-1) && ssize < MB_LEN_MAX) {
        /* Call with a buffer of adequate size */
        char s2[MB_LEN_MAX];
        size_t n2 = wcrtomb(s2, wc, ps);
        if (n2 != (size_t)(-1)) {
            if (n2 > ssize) {
                fputs("wcrtomb buffer overrun\n", stderr);
                abort();
            }
            memcpy(s, s2, n2);
        }
        return n2;
    }

    return wcrtomb(s, wc, ps);
}
