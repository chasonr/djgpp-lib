/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <limits.h>
#include <math.h>

double
remquo(double x, double y, int *quo)
{
    double rem = remainder(x, y);
    if (isfinite(x) && isfinite(y)) {
        double xi = remainder((x - rem) / y, 0x1.0p32);
        if (xi > INT_MAX) {
            xi -= 0x1.0p32;
        }
        *quo = xi;
    } else {
        *quo = 0;
    }
    return rem;
}
