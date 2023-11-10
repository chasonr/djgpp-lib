/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <errno.h>
#include <math.h>

double complex
csinh(double complex z)
{
    double x = __real__(z);
    double y = __imag__(z);

    /* ISO/IEC 9899:2018 G6.2.5 */
    if (isnan(x)) {
        if (isnan(y) || y == 0.0) {
            return z;
        }
    } else if (isinf(x)) {
        if (isnan(y) || y == 0.0) {
            return z;
        } else if (isinf(y)) {
            errno = EDOM;
            return CMPLX(INFINITY, 0.0/0.0);
        }
    } else if (isnan(y)) {
        if (x == 0.0) {
            return z;
        } else {
            return CMPLX(y, y);
        }
    } else if (isinf(y) && x == 0.0) {
        errno = EDOM;
        return CMPLX(x, 0.0/0.0);
    }

    double cx = cosh(x);
    double sx = sinh(x);
    double cy = cos(y);
    double sy = sin(y);
    return CMPLX(sx*cy, cx*sy);
}
