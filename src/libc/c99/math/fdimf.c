/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <math.h>

float
fdimf(float x, float y)
{
    if (isnan(x) || isnan(y)) {
        errno = EDOM;
        return x - y;
    }

    float diff = (x <= y) ? 0.0F : x - y;
    if (isinf(diff) && !(isinf(x) || isinf(y))) {
        errno = ERANGE;
    }
    return diff;
}
