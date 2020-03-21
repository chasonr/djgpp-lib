/* Copyright 2020 Ray Chason. See COPYING.DJ for details. */

#include <wctype.h>
#include "string.h"
#include "wcpriv.h"

wctrans_t wctrans(const char *property)
{
    if (strcmp(property, "tolower") == 0)
        return __dj_wc_towlower;
    if (strcmp(property, "toupper") == 0)
        return __dj_wc_towupper;

    return 0;
}
