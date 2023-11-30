/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

wchar_t *
__wcscat_chk(wchar_t * restrict s1, const wchar_t * restrict s2, size_t s1size)
{
    const char *err = NULL;

    if (s1size != (size_t)(-1)) {
        wchar_t *p1 = wmemchr(s1, L'\0', s1size);
        if (p1 == NULL) {
            err = "wcscat: destination buffer is full\n";
            goto fail;
        }
        size_t len1 = p1 - s1;

        size_t remaining = s1size - len1;
        const wchar_t *p2 = wmemchr(s2, L'\0', remaining);
        if (p2 == NULL) {
            err = "wcscat: destination buffer overrun\n";
            goto fail;
        }
    }

    return wcscat(s1, s2);

fail:
    fputs(err, stderr);
    abort();
}
