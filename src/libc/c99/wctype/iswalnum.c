/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
#include <wctype.h>

int
iswalnum(wint_t c)
{
    return iswalpha(c) || iswdigit(c);
}
