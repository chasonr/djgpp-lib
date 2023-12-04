/* Copyright (C) 2020, 2023 Ray Chason, see COPYING.DJ for details */
#include <wctype.h>
#include "../wchar/codepage.h"
#include "chrdata.h"
#include "wlowmap.h"

wint_t
towlower(wint_t c)
{
    wint_t c2 = __dj_find_map(c,
            to_lower, sizeof(to_lower)/sizeof(to_lower[0]));
    return c2 != WEOF ? c2 : c;
}
