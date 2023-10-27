/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <math.h>

long double
fdiml(long double x, long double y)
{
    if (isnan(x) || isnan(y)) {
        errno = EDOM;
        return x - y;
    }

    long double diff = (x <= y) ? 0.0L : x - y;
    if (isinf(diff) && !(isinf(x) || isinf(y))) {
        errno = ERANGE;
    }
    return diff;
}
