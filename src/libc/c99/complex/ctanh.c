/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>

double complex
ctanh(double complex z)
{
    double x = __real__(z);
    double y = __imag__(z);

    /* ISO/IEC 9899:2018 G6.2.6 */
    if (isnan(x)) {
        if (isnan(y) || y == 0.0) {
            return z;
        }
    } else if (isinf(x)) {
        if (isnan(y) || isinf(y)) {
            return CMPLX(copysign(1.0, x), copysign(0.0, y));
        } else {
            return CMPLX(copysign(1.0, x), copysign(0.0, sin(2.0*y)));
        }
    } else if (isnan(y)) {
        if (x == 0.0) {
            return z;
        } else {
            return CMPLX(y, y);
        }
    } else if (isinf(y)) {
        errno = EDOM;
        if (x == 0.0) {
            return CMPLX(x, 0.0/0.0);
        } else {
            return CMPLX(NAN, 0.0/0.0);
        }
    }

    bool neg = signbit(x);
    if (neg) {
        x = -x;
        y = -y;
    }

    double e2m = exp(-2.0*x);
    double e2m1 = -expm1(-2.0*x);

    double complex w = CMPLX(e2m1*(1.0+e2m), 2.0*e2m*sin(2.0*y))
                     / (1.0 + 2.0*e2m*cos(2.0*y) + e2m*e2m);

    if (neg) {
        w = -w;
    }

    return w;
}
