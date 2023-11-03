/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

long double
scalbnl(long double x, int exp)
{
    return ldexpl(x, exp);
}
