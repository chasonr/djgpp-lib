/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>
#include <stdbool.h>

double complex
casinh(double complex z)
{
    double x = __real__(z);
    double y = __imag__(z);

    /* ISO/IEC 8859:2018 G.6.2.2 */
    if (isnan(x)) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLX(y, x);
        }
    } else if (isinf(x)) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLX(x, copysign(3.14159265358979323846*0.25, y));
        } else {
            return CMPLX(x, copysign(0.0, y));
        }
    } else if (isinf(y)) {
        return CMPLX(copysign(INFINITY, x),
                     copysign(3.14159265358979323846*0.5, y));
    }

    if (y == 0.0) {
        return CMPLX(asinh(x), y);
    } else {
        bool neg = signbit(x);
        double complex za = neg ? -z : +z;
        double complex wa;
        if (fabs(x) > 1e18 || fabs(y) > 1e18) {
            /* za*za + 1 == za within machine precision; avoid premature
               overflow */
            wa = clog(za) + 0.693147180559945309417;
        } else {
            wa = clog(za + csqrt(za*za + 1.0));
        }
        double complex w = neg ? -wa : +wa;
        return w;
    }
}
