/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

float
roundf(float x)
{
    float xfrac, xint;

    if (!isfinite(x)) {
        return x;
    }

    xfrac = modff(x, &xint);
    if (xfrac >= 0.5F) {
        xint += 1.0F;
    } else if (xfrac <= -0.5F) {
        xint -= 1.0F;
    }

    return xint;
}
