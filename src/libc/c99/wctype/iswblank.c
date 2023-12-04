/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
#include <wctype.h>
#include "../wchar/codepage.h"

int
iswblank(wint_t c)
{
    if (!__dj_c_locale && c > 0x7F && c != 0x2028 && c != 0x2029) {
        return iswspace(c);
    }
    return c == L'\t' || c == L' ';
}
