/* Copyright 2020 Ray Chason. See COPYING.dj for details. */

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <wchar.h>

size_t
wcsrtombs(
        char * restrict dst,
        const wchar_t ** restrict src,
        size_t len,
        mbstate_t * restrict ps)
{
    static mbstate_t this_ps;
    size_t slen = wcslen(*src) + 1U; /* include the terminating null */
    size_t i = 0;
    size_t j = 0;

    if (ps == NULL) {
        ps = &this_ps;
    }
    while (i < slen && (j < len || dst == NULL)) {
        wchar_t wc = (*src)[i];
        char ch[MB_LEN_MAX];
        size_t l = wcrtomb(ch, wc, ps);
        if (l == (size_t)(-1) || l == (size_t)(-2)) {
            /* Error condition */
            errno = EILSEQ;
            return (size_t)(-1);
        }
        if (dst != NULL) {
            memcpy(dst+j, ch, l);
        }
        if (wc == L'\0') {
            break;
        }
        ++i;
        j += l;
    }

    if (dst != NULL) {
        *src += i;
    }
    return j;
}
