/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <math.h>
#include "bigfma.h"

double
fma(double x, double y, double z)
{
    if (!isfinite(x) || !isfinite(y) || !isfinite(z)) {
        return x*y + z;
    }
    if (x == 0.0 || y == 0.0 || z == 0.0) {
        // Return zero with correct sign
        return x*y + z;
    }

    long double sum[3];
    __dj_big_fma((long double)x, (long double)y, (long double)z, sum);

    if (isfinite(sum[0])) {
        if (sum[1] != 0.0 || sum[2] != 0.0) {
            sum[0] = __dj_set_odd(sum[0]);
        }
    }

    double dsum = (double)sum[0];
    if (!isfinite(dsum)) {
        errno = ERANGE;
    }
    return dsum;
}
