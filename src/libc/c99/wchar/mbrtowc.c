/* Copyright 2020 Ray Chason. See COPYING.dj for details. */

#include <wchar.h>
#include <errno.h>
#include "codepage.h"

size_t
mbrtowc(wchar_t * __restrict__ pwc,
        const char * __restrict__ s, size_t n,
        mbstate_t * __restrict__ ps)
{
    const struct char_conv *table = __dj_get_conversion();
    wint_t wch;
    int rc;

    if (s == NULL || n == 0) {
        return 0;
    }

    wch = __dj_single_map(table, (unsigned char)s[0]);
    if (wch == WEOF) {
        /* invalid byte */
        errno = EILSEQ;
        rc = -1;
    } else {
        if (pwc != NULL) {
            *pwc = wch;
        }
        rc = 1;
    }
    return (size_t)rc;
}
