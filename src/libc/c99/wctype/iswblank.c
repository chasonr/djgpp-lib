/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */
#include <wctype.h>

int iswblank(wint_t c)
{
    /*
     * ISO C, 7.30.2.1.3: "In the 'C' locale, iswblank returns true only for
     * the standard blank characters."
     */
    return c == L' ' || c == L'\t';
}
