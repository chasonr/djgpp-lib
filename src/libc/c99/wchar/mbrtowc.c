/* Copyright 2020, 2023 Ray Chason. See COPYING.dj for details. */

#include <wchar.h>
#include <uchar.h>

size_t
mbrtowc(wchar_t * __restrict__ pwc,
        const char * __restrict__ s, size_t n,
        mbstate_t * __restrict__ ps)
{
    static mbstate_t this_ps;

    if (ps == NULL) {
        ps = &this_ps;
    }

    char16_t c16;
    size_t size = mbrtoc16(&c16, s, n, ps);
    if (size <= n || size == (size_t)(-3)) {
        *pwc = (wchar_t)c16;
    }
    return size;
}
