/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *
__strncat_chk(char * restrict s1, const char * restrict s2, size_t n, size_t s1size)
{
    const char *err = NULL;

    if (s1size != (size_t)(-1)) {
        char *p1 = memchr(s1, '\0', s1size);
        if (p1 == NULL) {
            err = "strncat: destination buffer is full\n";
            goto fail;
        }
        size_t len1 = p1 - s1;

        const char *p2 = memchr(s2, '\0', n);
        size_t len2 = p2 ? (size_t)(p2 - s2) : n;

        if (len1 + len2 + 1 > s1size) {
            err = "strncat: destination buffer overrun\n";
            goto fail;
        }
    }

    return strncat(s1, s2, n);

fail:
    fputs(err, stderr);
    abort();
}
