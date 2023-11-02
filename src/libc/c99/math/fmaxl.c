/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

long double
fmaxl(long double x, long double y)
{
    return (isgreaterequal(x, y) || isnan(y)) ? x : y;
}
