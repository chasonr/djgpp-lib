/* Copyright 2020, 2023 Ray Chason. See COPYING.dj for details. */

#include <uchar.h>
#include <wchar.h>

size_t
wcrtomb(char * __restrict__ s, wchar_t wc,
        mbstate_t * __restrict__ ps)
{
    static mbstate_t this_ps;
    return c16rtomb(s, (char16_t)wc, ps ? ps : &this_ps);
}
