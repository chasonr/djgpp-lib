/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */
#include <wchar.h>

size_t
mbrlen(const char * __restrict__ s, size_t n, mbstate_t * __restrict__ ps)
{
    static mbstate_t shift;
    return mbrtowc(NULL, s, n, ps ? ps : &shift);
}
