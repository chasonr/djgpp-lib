/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <errno.h>
#include <math.h>

long double complex
csinhl(long double complex z)
{
    long double x = __real__(z);
    long double y = __imag__(z);

    /* ISO/IEC 9899:2018 G6.2.5 */
    if (isnan(x)) {
        if (isnan(y) || y == 0.0L) {
            return z;
        }
    } else if (isinf(x)) {
        if (isnan(y) || y == 0.0L) {
            return z;
        } else if (isinf(y)) {
            errno = EDOM;
            return CMPLXF(INFINITY, 0.0L/0.0L);
        }
    } else if (isnan(y)) {
        if (x == 0.0L) {
            return z;
        } else {
            return CMPLXF(y, y);
        }
    } else if (isinf(y) && x == 0.0L) {
        errno = EDOM;
        return CMPLXF(x, 0.0L/0.0L);
    }

    long double cx = coshl(x);
    long double sx = sinhl(x);
    long double cy = cosl(y);
    long double sy = sinl(y);
    return CMPLXF(sx*cy, cx*sy);
}
