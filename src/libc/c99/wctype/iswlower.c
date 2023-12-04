/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
#include <wctype.h>
#include "../wchar/codepage.h"
#include "chrdata.h"
#include "wlower.h"

int
iswlower(wint_t c)
{
    if (__dj_c_locale && c > 0x7F) {
        return 0;
    }
    return __dj_find_range(c, lower, sizeof(lower)/sizeof(lower[0]));
}
