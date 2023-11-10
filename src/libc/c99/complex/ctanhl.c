/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>

long double complex
ctanhl(long double complex z)
{
    long double x = __real__(z);
    long double y = __imag__(z);

    /* ISO/IEC 9899:2018 G6.2.6 */
    if (isnan(x)) {
        if (isnan(y) || y == 0.0L) {
            return z;
        }
    } else if (isinf(x)) {
        if (isnan(y) || isinf(y)) {
            return CMPLXL(copysignl(1.0L, x), copysignl(0.0L, y));
        } else {
            return CMPLXL(copysignl(1.0L, x), copysignl(0.0L, sin(2.0L*y)));
        }
    } else if (isnan(y)) {
        if (x == 0.0L) {
            return z;
        } else {
            return CMPLXL(y, y);
        }
    } else if (isinf(y)) {
        errno = EDOM;
        if (x == 0.0L) {
            return CMPLXL(x, 0.0L/0.0L);
        } else {
            return CMPLXL(NAN, 0.0L/0.0L);
        }
    }

    bool neg = signbit(x);
    if (neg) {
        x = -x;
        y = -y;
    }

    long double e2m = expl(-2.0L*x);
    long double e2m1 = -expm1l(-2.0L*x);

    long double complex w = CMPLXL(e2m1*(1.0L+e2m), 2.0L*e2m*sinl(2.0L*y))
                          / (1.0L + 2.0L*e2m*cosl(2.0L*y) + e2m*e2m);

    if (neg) {
        w = -w;
    }

    return w;
}
