/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

float
scalbnf(float x, int exp)
{
    return ldexpf(x, exp);
}
