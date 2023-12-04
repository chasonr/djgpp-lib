/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
#include <wctype.h>
#include "../wchar/codepage.h"
#include "chrdata.h"
#include "wspace.h"

int
iswspace(wint_t c)
{
    if (__dj_c_locale && c > 0x7F) {
        return 0;
    }
    return __dj_find_range(c, space, sizeof(space)/sizeof(space[0]));
}
