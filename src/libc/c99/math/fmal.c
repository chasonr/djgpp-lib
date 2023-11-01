/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <math.h>
#include "bigfma.h"

long double
fmal(long double x, long double y, long double z)
{
    if (!isfinite(x) || !isfinite(y) || !isfinite(z)) {
        return x*y + z;
    }
    if (x == 0.0L || y == 0.0L || z == 0.0L) {
        // Return zero with correct sign
        return x*y + z;
    }

    long double sum[3];
    __dj_big_fma(x, y, z, sum);

    if (isfinite(sum[0])) {
        if (sum[2] != 0.0L) {
            sum[1] = __dj_set_odd(sum[1]);
        }
    }

    long double lsum = sum[0] + sum[1];
    if (!isfinite(lsum)) {
        errno = ERANGE;
    }
    return lsum;
}
