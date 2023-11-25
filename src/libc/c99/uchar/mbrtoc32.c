/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <uchar.h>
#include <wchar.h>
#include "../wchar/codepage.h"

size_t
mbrtoc32(char32_t * restrict pc32, const char * restrict s, size_t n,
         mbstate_t * restrict ps)
{
    static mbstate_t this_ps;
    char32_t dummy;

    if (ps == NULL) {
        ps = &this_ps;
    }
    if (pc32 == NULL) {
        pc32 = &dummy;
    }

    if (s == NULL || n == 0) {
        return 0;
    }

    if (__dj_is_utf8()) {
        size_t count = 0;

        if (ps->_num_bytes == 0) {
            /* Next byte is the start of a character */
            unsigned char byte = (unsigned char)s[0];
            if (byte < 0x80) {
                /* Single byte character */
                *pc32 = (char32_t)byte;
                return byte != 0 ? 1 : 0;
            } else if (byte < 0xC2) {
                /* 80-BF: Dangling continuation byte */
                /* C0-C1: Two byte encoding of one byte character */
                errno = EILSEQ;
                return (size_t)(-1);
            } else if (byte < 0xE0) {
                /* Two byte character */
                ps->_num_bytes = 1;
                ps->_codepoint = byte & 0x1F;
            } else if (byte < 0xF0) {
                /* Three byte character */
                ps->_num_bytes = 2;
                ps->_codepoint = byte & 0x0F;
            } else if (byte < 0xF5) {
                /* Four byte character */
                ps->_num_bytes = 3;
                ps->_codepoint = byte & 0x07;
            } else {
                /* These bytes cannot appear in UTF-8 */
                errno = EILSEQ;
                return (size_t)(-1);
            }
            count = 1;
        }

        while (ps->_num_bytes != 0 && count < n) {
            unsigned char byte = (unsigned char)s[count];
            if (byte < 0x80 || 0xBF < byte) {
                /* Invalid continuation byte */
                errno = EILSEQ;
                return (size_t)(-1);
            }

            /* Check for invalid UTF-8 encodings */
            switch (ps->_num_bytes) {
            case 2:
                if (ps->_codepoint == 0x00 && byte < 0xA0) {
                    /* Three byte encoding of two byte character */
                    errno = EILSEQ;
                    return (size_t)(-1);
                }
                if (ps->_codepoint == 0x0D && byte > 0x9F) {
                    /* Surrogate code point */
                    errno = EILSEQ;
                    return (size_t)(-1);
                }
                break;

            case 3:
                if (ps->_codepoint == 0x00 && byte < 0x90) {
                    /* Four byte encoding of shorter character */
                    errno = EILSEQ;
                    return (size_t)(-1);
                }
                if (ps->_codepoint == 0x04 && byte > 0x8F) {
                    /* Code point not in Unicode */
                    errno = EILSEQ;
                    return (size_t)(-1);
                }
                break;
            }

            /* Add byte to code point */
            ps->_codepoint = (ps->_codepoint << 6) | (byte & 0x3F);
            --ps->_num_bytes;
            ++count;
        }

        if (ps->_num_bytes != 0) {
            /* Character is incomplete */
            return (size_t)(-2);
        } else {
            /* Character is complete */
            *pc32 = ps->_codepoint;
            return count;
        }
    } else {
        const struct char_conv *table = __dj_get_conversion();
        wint_t wch = __dj_single_map(table, s[0] & 0xFF);
        if (wch != WEOF) {
            if (pc32 != NULL) {
                *pc32 = (char32_t)wch;
            }
            return wch ? 1 : 0;
        } else {
            errno = EILSEQ;
            return (size_t)-1;
        }
    }
}
