/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

float
scalblnf(float x, long exp)
{
    /* long is the same size as int */
    return ldexpf(x, (int)exp);
}
