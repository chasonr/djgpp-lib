/* Copyright 2020 Ray Chason. See COPYING.dj for details. */

#include <errno.h>
#include <string.h>
#include <wchar.h>

size_t
mbsrtowcs(
        wchar_t * __restrict__ dst,
        const char ** __restrict__ src,
        size_t len,
        mbstate_t * __restrict__ ps)
{
    static mbstate_t this_ps;
    size_t slen = strlen(*src) + 1U; /* include the terminating null */
    size_t i = 0;
    size_t j = 0;

    if (ps == NULL) {
        ps = &this_ps;
    }
    while (i < slen && (j < len || dst == NULL)) {
        wchar_t wc;
        size_t l = mbrtowc(&wc, *src + i, slen - i, ps);
        if (l == (size_t)(-1) || l == (size_t)(-2)) {
            /* Error condition */
            errno = EILSEQ;
            return (size_t)(-1);
        }
        if (dst != NULL) {
            dst[j] = wc;
        }
        if (wc == L'\0') {
            break;
        }
        i += l;
        ++j;
    }

    if (dst != NULL) {
        *src += i;
    }
    return j;
}
