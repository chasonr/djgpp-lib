/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <uchar.h>
#include <wchar.h>
#include "../wchar/codepage.h"

size_t
mbrtoc16(char16_t * restrict pc16, const char * restrict s, size_t n,
         mbstate_t * restrict ps)
{
    if (s == NULL || n == 0) {
        return 0;
    }

    const struct char_conv *table = __dj_get_conversion();
    wint_t wch = __dj_single_map(table, s[0] & 0xFF);
    if (wch != WEOF) {
        if (pc16 != NULL) {
            *pc16 = (char16_t)wch;
        }
        return wch ? 1 : 0;
    } else {
        errno = EILSEQ;
        return (size_t)-1;
    }
}
