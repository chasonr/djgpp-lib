/* Copyright 2020 Ray Chason. See COPYING.dj for details. */

#include <wchar.h>
#include "codepage.h"

wint_t
btowc(int ch)
{
    const struct char_conv *table = __dj_get_conversion();
    return __dj_single_map(table, ch);
}
