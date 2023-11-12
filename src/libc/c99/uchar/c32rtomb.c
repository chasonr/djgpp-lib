/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <stdio.h> // EOF
#include <string.h>
#include <uchar.h>
#include <wchar.h>
#include "../wchar/codepage.h"

size_t
c32rtomb(char * restrict s, char32_t c32, mbstate_t * restrict ps)
{
    static mbstate_t this_ps;

    if (ps == NULL) {
        ps = &this_ps;
    }

    if (s == NULL || c32 == 0) {
        memset(ps, 0, sizeof(*ps));
        if (s != NULL) {
            s[0] = '\0';
        }
        return 1;
    } else {
        if (__dj_is_utf8()) {
            if (c32 > 0x10FFFF || (0xD800 <= c32 && c32 <= 0xDFFF)) {
                errno = EILSEQ;
                return (size_t)(-1);
            }
            if (c32 < 0x80) {
                s[0] = (char)c32;
                return 1;
            } else if (c32 < 0x800) {
                s[0] = (char)(0xC0 | (c32 >> 6));
                s[1] = (char)(0x80 | (c32 & 0x3F));
                return 2;
            } else if (c32 < 0x10000) {
                s[0] = (char)(0xE0 | (c32 >> 12));
                s[1] = (char)(0x80 | ((c32 >> 6) & 0x3F));
                s[2] = (char)(0x80 | (c32 & 0x3F));
                return 3;
            } else {
                s[0] = (char)(0xF0 | (c32 >> 18));
                s[1] = (char)(0x80 | ((c32 >> 12) & 0x3F));
                s[2] = (char)(0x80 | ((c32 >> 6) & 0x3F));
                s[3] = (char)(0x80 | (c32 & 0x3F));
                return 4;
            }
        } else {
            if (c32 > 0xFFFF) {
                errno = EILSEQ;
                return (size_t)(-1);
            }

            const struct char_conv *table = __dj_get_conversion();
            int ch = __dj_single_unmap(table, c32);
            if (ch == EOF) {
                errno = EILSEQ;
                return (size_t)(-1);
            }
            s[0] = (char)ch;
            return ch ? 1 : 0;
        }
    }
}
