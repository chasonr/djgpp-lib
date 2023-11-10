/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>
#include <stdbool.h>

double complex
csqrt(double complex z)
{
    /* ISO/IEC 9899:2018, G.6.4.2 */
    if (isnan(__imag__(z))) {
        if (isnan(__real__(z)) || __real__(z) == +INFINITY) {
            return z;
        } else if (__real__(z) == -INFINITY) {
            return CMPLX(__imag__(z), copysign(INFINITY, __imag__(z)));
        } else {
            return CMPLX(__imag__(z), __imag__(z));
        }
    }
    if (isinf(__imag__(z))) {
        return CMPLX(INFINITY, __imag__(z)); /* even if __real__(z) is NaN */
    }
    if (isnan(__real__(z))) {
        return CMPLX(__real__(z), __real__(z));
    }
    if (__real__(z) == +INFINITY) {
        return CMPLX(+INFINITY, copysign(0.0, __imag__(z)));
    }
    if (__real__(z) == -INFINITY) {
        return CMPLX(0.0, copysign(INFINITY, __imag__(z)));
    }

    if (__imag__(z) == 0.0) {
        double w = sqrt(fabs(__real__(z)));
        if (signbit(__real__(z))) {
            return CMPLX(0.0, copysign(w, __imag__(z)));
        } else {
            return CMPLX(w, __imag__(z));
        }
    } else {
        /* Avoid overflow in cabs */
        bool scale = fabs(__real__(z)) > 1e36 || fabs(__imag__(z)) > 1e36;
        if (scale) {
            z /= 4.0;
        }
        double r = cabs(z);
        double a = carg(z);
        r = sqrt(r);
        a /= 2.0;
        double complex w = CMPLX(r*cos(a), r*sin(a));
        if (scale) {
            w *= 2.0;
        }
        return w;
    }
}
