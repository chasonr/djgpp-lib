/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

double
fmin(double x, double y)
{
    return (islessequal(x, y) || isnan(y)) ? x : y;
}
