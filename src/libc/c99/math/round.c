/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

double
round(double x)
{
    double xfrac, xint;

    if (!isfinite(x)) {
        return x;
    }

    xfrac = modf(x, &xint);
    if (xfrac >= 0.5) {
        xint += 1.0;
    } else if (xfrac <= -0.5) {
        xint -= 1.0;
    }

    return xint;
}
