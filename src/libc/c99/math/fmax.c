/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

double
fmax(double x, double y)
{
    return (isgreaterequal(x, y) || isnan(y)) ? x : y;
}
