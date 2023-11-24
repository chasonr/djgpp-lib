/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <string.h>
#include <uchar.h>
#include <wchar.h>
#include "../wchar/codepage.h"

size_t
mbrtoc16(char16_t * restrict pc16, const char * restrict s, size_t n,
         mbstate_t * restrict ps)
{
    static mbstate_t this_ps;
    char16_t dummy;

    if (ps == NULL) {
        ps = &this_ps;
    }
    if (pc16 == NULL) {
        pc16 = &dummy;
    }

    if (s == NULL) {
        memset(ps, 0, sizeof(*ps));
        return 0;
    }

    if (__dj_is_utf8()) {
        if (ps->_surrogate != 0) {
            /* Return trailing surrogate */
            *pc16 = ps->_surrogate;
            ps->_surrogate = 0;
            return (size_t)(-3);
        } else {
            char32_t ch32 = 0;
            size_t count = mbrtoc32(&ch32, s, n, ps);
            if (count <= n) {
                /* ch32 contains a valid UTF-32 character */
                if (ch32 < 0x10000) {
                    /* Basic Multilingual Plane character */
                    *pc16 = (char16_t)ch32;
                } else {
                    /* Supplementary character */
                    *pc16 = (char16_t)((ch32 >> 10) + 0xD7C0);
                    ps->_surrogate = (char16_t)((ch32 & 0x3FF) + 0xDC00);
                }
            }
            return count;
        }
    } else {
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
}
