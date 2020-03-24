/* Copyright 2020 Ray Chason. See COPYING.dj for details. */

#include <errno.h>
#include <stdio.h>
#include <wchar.h>
#include "codepage.h"

size_t
wcrtomb(char * __restrict__ s, wchar_t wc,
        mbstate_t * __restrict__ ps)
{
    const struct char_conv *table = __dj_get_conversion();
    int ch;

    ch = __dj_single_unmap(table, wc);
    if (ch != EOF) {
        if (s != NULL) {
            s[0] = (char)ch;
        }
        return 1;
    }

    /* Conversion failed */
    errno = EILSEQ;
    return (size_t)(-1);
}
