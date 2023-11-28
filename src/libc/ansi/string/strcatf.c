/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *
__strcat_chk(char * restrict s1, const char * restrict s2, size_t s1size)
{
    const char *err = NULL;

    if (s1size != (size_t)(-1)) {
        char *p1 = memchr(s1, '\0', s1size);
        if (p1 == NULL) {
            err = "strcat: destination buffer is full\n";
            goto fail;
        }
        size_t len1 = p1 - s1;

        size_t remaining = s1size - len1;
        const char *p2 = memchr(s2, '\0', remaining);
        if (p2 == NULL) {
            err = "strcat: destination buffer overrun\n";
            goto fail;
        }
    }

    return strcat(s1, s2);

fail:
    fputs(err, stderr);
    abort();
}
