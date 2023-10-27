/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <math.h>

double
fdim(double x, double y)
{
    if (isnan(x) || isnan(y)) {
        errno = EDOM;
        return x - y;
    }

    double diff = (x <= y) ? 0.0 : x - y;
    if (isinf(diff) && !(isinf(x) || isinf(y))) {
        errno = ERANGE;
    }
    return diff;
}
