/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <stdio.h> // EOF
#include <string.h>
#include <uchar.h>
#include <wchar.h>
#include "../wchar/codepage.h"

size_t
c16rtomb(char * restrict s, char16_t c16, mbstate_t * restrict ps)
{
    static mbstate_t this_ps;

    if (ps == NULL) {
        ps = &this_ps;
    }

    if (s == NULL || c16 == 0) {
        memset(ps, 0, sizeof(*ps));
        if (s != NULL) {
            s[0] = '\0';
        }
        return 1;
    } else {
        /* UTF-16 to UTF-32 conversion */
        char32_t c32 = 0;

        if (ps->_surrogate != 0) {
            if (0xDC00 <= c16 && c16 <= 0xDFFF) {
                /* Trailing surrogate */
                c32 = ((char32_t)(ps->_surrogate - 0xD7C0) << 10)
                    | (c16 & 0x3FF);
                ps->_surrogate = 0;
            } else {
                /* Trailing surrogate was required */
                errno = EILSEQ;
                return (size_t)(-1);
            }
        } else {
            if (0xD800 <= c16 && c16 <= 0xDBFF) {
                /* Leading surrogate */
                ps->_surrogate = c16;
                return 0;
            } else if (0xDC00 <= c16 && c16 <= 0xDFFF) {
                /* Invalid trailing surrogate */
                errno = EILSEQ;
                return (size_t)(-1);
            } else {
                /* Single code point */
                c32 = (char32_t)c16;
            }
        }

        return c32rtomb(s, c32, ps);
    }
}
