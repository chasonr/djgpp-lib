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

    return mbrtoc16((char16_t *)pwc, s, n, ps);
}
