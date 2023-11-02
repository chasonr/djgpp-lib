/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

float
fmaxf(float x, float y)
{
    return (isgreaterequal(x, y) || isnan(y)) ? x : y;
}
