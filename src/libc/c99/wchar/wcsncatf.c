/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

wchar_t *
__wcsncat_chk(wchar_t * restrict s1, const wchar_t * restrict s2, size_t n, size_t s1size)
{
    const char *err = NULL;

    if (s1size != (size_t)(-1)) {
        wchar_t *p1 = wmemchr(s1, L'\0', s1size);
        if (p1 == NULL) {
            err = "wcsncat: destination buffer is full\n";
            goto fail;
        }
        size_t len1 = p1 - s1;

        const wchar_t *p2 = wmemchr(s2, L'\0', n);
        size_t len2 = p2 ? (size_t)(p2 - s2) : n;

        if (len1 + len2 + 1 > s1size) {
            err = "wcsncat: destination buffer overrun\n";
            goto fail;
        }
    }

    return wcsncat(s1, s2, n);

fail:
    fputs(err, stderr);
    abort();
}
