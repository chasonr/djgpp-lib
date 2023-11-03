/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

long double
scalblnl(long double x, long exp)
{
    /* long is the same size as int */
    return ldexpl(x, (int)exp);
}
