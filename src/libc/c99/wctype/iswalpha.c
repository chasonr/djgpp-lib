/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
#include <wctype.h>
#include "../wchar/codepage.h"
#include "chrdata.h"
#include "walpha.h"

int
iswalpha(wint_t c)
{
    if (__dj_c_locale && c > 0x7F) {
        return 0;
    }
    return __dj_find_range(c, alpha, sizeof(alpha)/sizeof(alpha[0]));
}
