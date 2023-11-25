/* Copyright 2020, 2023 Ray Chason. See COPYING.dj for details. */

#include <wchar.h>
#include <errno.h>
#include <string.h>
#include <uchar.h>
#include "codepage.h"

size_t
mbrtowc(wchar_t * __restrict__ pwc,
        const char * __restrict__ s, size_t n,
        mbstate_t * __restrict__ ps)
{
    static mbstate_t this_ps;
    wchar_t dummy;

    if (ps == NULL) {
        ps = &this_ps;
    }
    if (pwc == NULL) {
        pwc = &dummy;
    }

    if (s == NULL) {
        memset(ps, 0, sizeof(*ps));
        return 0;
    }

    /*
     * mbrtowc is not allowed to return (size_t)(-3), so a different approach
     * is needed for supplementary characters.
     * Convert the first three bytes to the leading surrogate, and save state
     * so the fourth byte can produce the trailing surrogate.
     */
    if (__dj_is_utf8()) {
        char32_t ch32 = 0;
        size_t count = mbrtoc32(&ch32, s, n, ps);
        if (ch32 > 0xFFFF) {
            --count;
            wchar_t ch1 = 0xD7C0 + (ch32 >> 10);
            wchar_t ch2 = 0xDC00 + (ch32 & 0xFF);
            if (pwc != NULL) {
                *pwc = ch1;
            }
            /* Set the multibyte state so the next byte produces the trailing
               surrogate */
            ps->_codepoint = ch2 >> 6;
            ps->_num_bytes = 1;
        } else if (count == (size_t)(-2)) {
            /* Are we one byte short of a supplementary character? */
            if (ps->_codepoint >= 0x400 && ps->_num_bytes == 1) {
                count = n;
                if (pwc != NULL) {
                    *pwc = 0xD7C0 + (ps->_codepoint >> 4);
                }
                /* Set the multibyte state so the next byte produces the trailing
                   surrogate */
                ps->_codepoint = 0x370 | (ps->_codepoint & 0xF);
            }
        } else if (count != (size_t)(-1)) {
            if (pwc != NULL) {
                *pwc = (wchar_t)ch32;
            }
        }
        return count;
    } else {
        const struct char_conv *table = __dj_get_conversion();
        wint_t wch = __dj_single_map(table, s[0] & 0xFF);
        if (wch != WEOF) {
            if (pwc != NULL) {
                *pwc = (wchar_t)wch;
            }
            return wch ? 1 : 0;
        } else {
            errno = EILSEQ;
            return (size_t)-1;
        }
    }
}
