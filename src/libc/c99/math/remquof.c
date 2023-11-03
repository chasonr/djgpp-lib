/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <limits.h>
#include <math.h>

float
remquof(float x, float y, int *quo)
{
    float rem = remainderf(x, y);
    if (isfinite(x) && isfinite(y)) {
        float xi = remainderf((x - rem) / y, 0x1.0p32F);
        if (xi > INT_MAX) {
            xi -= 0x1.0p32F;
        }
        *quo = xi;
    } else {
        *quo = 0;
    }
    return rem;
}
