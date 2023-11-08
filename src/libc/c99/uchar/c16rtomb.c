/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <stdio.h> // EOF
#include <uchar.h>
#include <wchar.h>
#include "../wchar/codepage.h"

size_t
c16rtomb(char * restrict s, char16_t c16, mbstate_t * restrict ps)
{
    if (s == NULL) {
        return 0;
    }

    const struct char_conv *table = __dj_get_conversion();
    int ch = __dj_single_unmap(table, c16);
    if (ch == EOF) {
        errno = EILSEQ;
        return (size_t)(-1);
    }
    s[0] = (char)ch;
    return ch ? 1 : 0;
}
