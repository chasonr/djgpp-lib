/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

float
roundf(float x)
{
    float y;

    if (signbit(x)) {
        y = ceilf(x - 0.5F);
    } else {
        y = floorf(x + 0.5F);
    }
    return y;
}
