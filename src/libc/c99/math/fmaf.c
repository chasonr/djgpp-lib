/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <math.h>
#include "bigfma.h"

float
fmaf(float x, float y, float z)
{
    if (!isfinite(x) || !isfinite(y) || !isfinite(z)) {
        // Raise any relevant exceptions
        return x*y + z;
    }

    // Multiply x * y
    long double prod = (long double)x * (long double)y;

    // Add z to the product
    long double err;
    long double sum = __dj_two_sum(prod, (long double)z, &err);

    if (isfinite(sum) && err != 0.0L) {
        sum = __dj_set_odd(sum);
    }

    float fsum = (float)sum;
    if (!isfinite(fsum)) {
        errno = ERANGE;
    }
    return fsum;
}
