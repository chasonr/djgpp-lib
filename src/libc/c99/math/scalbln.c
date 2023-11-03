/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

double
scalbln(double x, long exp)
{
    /* long is the same size as int */
    return ldexp(x, (int)exp);
}
