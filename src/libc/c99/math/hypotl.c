/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <float.h>
#include <math.h>

long double
hypotl(long double x, long double y)
{
    /* hypotl(inf, nan) should return infinity */
    if (isinf(x) || isinf(y)) {
        return INFINITY;
    }
    /* Return NaN if one was otherwise passed */
    if (isnan(x)) {
        return x;
    }
    if (isnan(y)) {
        return y;
    }

    /* x and y are both finite */
    /* Using the absolute values simplifies later checks */

    long double xa = fabsl(x);
    long double ya = fabsl(y);

    /* Avoid premature overflow by scaling */
    /* Scale by powers of two, using ldexpl, so the scaling does not become a
       source of roundoff error */

    if (xa < ya) {
        long double s = xa;
        xa = ya;
        ya = s;
    }
    int ex;
    frexpl(xa, &ex);
    int scale = (LDBL_MAX_EXP / 2 - 1) - ex;
    xa = ldexpl(xa, scale);
    ya = ldexpl(ya, scale);

    /* Compute the hypotenuse */
    long double z = sqrtl(xa*xa + ya*ya);
    z = ldexpl(z, -scale);

    /* Indicate error if overflow */
    if (isinf(z)) {
        errno = ERANGE;
    }

    return z;
}
