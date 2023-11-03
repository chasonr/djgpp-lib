/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <limits.h>
#include <math.h>

long double
remquol(long double x, long double y, int *quo)
{
    long double rem = remainderl(x, y);
    if (isfinite(x) && isfinite(y)) {
        long double xi = remainderl((x - rem) / y, 0x1.0p32L);
        if (xi > INT_MAX) {
            xi -= 0x1.0p32L;
        }
        *quo = xi;
    } else {
        *quo = 0;
    }
    return rem;
}
