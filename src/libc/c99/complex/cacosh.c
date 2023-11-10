/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

double complex
cacosh(double complex z)
{
    double x = __real__(z);
    double y = __imag__(z);

    /* ISO/IEC 9899:2018 G.6.2.1 */
    if (isnan(x)) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLX(+INFINITY, x);
        } else {
            return CMPLX(x, x);
        }
    } else if (x == -INFINITY) {
        if (isnan(y)) {
            return CMPLX(+INFINITY, y);
        } else if (isinf(y)) {
            return CMPLX(+INFINITY, copysign(3.14159265358979323846*0.75, y));
        } else {
            return CMPLX(+INFINITY, copysign(3.14159265358979323846, y));
        }
    } else if (x == +INFINITY) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLX(+INFINITY, copysign(3.14159265358979323846*0.25, y));
        } else {
            return CMPLX(+INFINITY, copysign(0.0, y));
        }
    } else if (isnan(y)) {
        if (x == 0.0) {
            return CMPLX(y, +3.14159265358979323846*0.5);
        } else {
            return CMPLX(y, y);
        }
    } else if (isinf(y)) {
        return CMPLX(+INFINITY, copysign(+3.14159265358979323846*0.5, y));
    }

    if (y == 0.0) {
        if (x < -1.0) {
            return CMPLX(acosh(-x),
                         copysign(+3.14159265358979323846, y));
        } else if (x <= +1.0) {
            return CMPLX(+0.0, copysign(acos(x), y));
        } else {
            return CMPLX(acosh(+x), y);
        }
    } else {
        double complex w;
        if (fabs(x) > 1e18 || fabs(y) > 1e18) {
            /* z*z + 1 == z within machine precision; avoid premature
               overflow */
            w = clog(z) + 0.693147180559945309417;
        } else {
            w = clog(z + csqrt(z + 1.0)*csqrt(z - 1.0));
        }
        /* Deal with cancellations */
        w -= (ccosh(w) - z)/csinh(w);
        if (signbit(x)) {
            w = -w;
        }
        return w;
    }
}
