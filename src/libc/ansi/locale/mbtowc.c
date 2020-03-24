/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdlib.h>
#include <wchar.h>

int
mbtowc(wchar_t * __restrict__ pwc, const char * __restrict__ s, size_t n)
{
    static mbstate_t shift;
    if (s == 0) {
        return 0; /* no state-dependent encodings */
    }
    return mbrtowc(pwc, s, n, &shift);
}
