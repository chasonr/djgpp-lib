/* Copyright 2020 Ray Chason. See COPYING.DJ for details. */

#include <wctype.h>
#include "wcpriv.h"

wint_t towctrans(wint_t wc, wctrans_t desc)
{
    wint_t wc2;

    switch (desc)
    {
    case __dj_wc_towlower:
        wc2 = towlower(wc);
        break;

    case __dj_wc_towupper:
        wc2 = towupper(wc);
        break;

    default:
        wc2 = wc;
        break;
    }

    return wc2;
}
