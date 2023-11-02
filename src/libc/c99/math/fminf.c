/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

float
fminf(float x, float y)
{
    return (islessequal(x, y) || isnan(y)) ? x : y;
}
