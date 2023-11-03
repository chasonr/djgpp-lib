/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

long double
roundl(long double x)
{
    long double xfrac, xint;

    if (!isfinite(x)) {
        return x;
    }

    xfrac = modfl(x, &xint);
    if (xfrac >= 0.5L) {
        xint += 1.0L;
    } else if (xfrac <= -0.5L) {
        xint -= 1.0L;
    }

    return xint;
}
