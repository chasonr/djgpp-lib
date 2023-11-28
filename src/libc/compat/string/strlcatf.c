/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t
__strlcat_chk(char * restrict dest, const char * restrict src, size_t size, size_t destsize)
{
    const char *err = NULL;

    if (destsize != (size_t)(-1)) {
        char *p1 = memchr(dest, '\0', destsize);
        if (p1 == NULL) {
            err = "strlcat: destination buffer is full\n";
            goto fail;
        }
        size_t dlen = p1 - dest;
        if (dlen >= size) {
            goto pass; /* strlcat will write nothing */
        }

        size_t remaining = size - dlen; /* this is at least 1 */
        const char *p2 = memchr(src, '\0', remaining - 1);
        size_t slen = p2 ? (size_t)(p2 - src) : remaining - 1;
        if (dlen + slen + 1 > destsize) {
            err = "strlcat: destination buffer overrun\n";
            goto fail;
        }
    }

pass:
    return strlcat(dest, src, size);

fail:
    fputs(err, stderr);
    abort();
}
