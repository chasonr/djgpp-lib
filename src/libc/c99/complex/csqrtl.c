/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>
#include <stdbool.h>

long double complex
csqrtl(long double complex z)
{
    /* ISO/IEC 9899:2018, G.6.4.2 */
    if (isnan(__imag__(z))) {
        if (isnan(__real__(z)) || __real__(z) == +INFINITY) {
            return z;
        } else if (__real__(z) == -INFINITY) {
            return CMPLXL(__imag__(z), copysignl(INFINITY, __imag__(z)));
        } else {
            return CMPLXL(__imag__(z), __imag__(z));
        }
    }
    if (isinf(__imag__(z))) {
        return CMPLXL(INFINITY, __imag__(z)); /* even if __real__(z) is NaN */
    }
    if (isnan(__real__(z))) {
        return CMPLXL(__real__(z), __real__(z));
    }
    if (__real__(z) == +INFINITY) {
        return CMPLXL(+INFINITY, copysignl(0.0L, __imag__(z)));
    }
    if (__real__(z) == -INFINITY) {
        return CMPLXL(0.0L, copysignl(INFINITY, __imag__(z)));
    }

    if (__imag__(z) == 0.0L) {
        long double w = sqrtl(fabsl(__real__(z)));
        if (signbit(__real__(z))) {
            return CMPLXL(0.0L, copysignl(w, __imag__(z)));
        } else {
            return CMPLXL(w, __imag__(z));
        }
    } else {
        /* Avoid overflow in cabsl */
        bool scale = fabsl(__real__(z)) > 1e36L || fabsl(__imag__(z)) > 1e36L;
        if (scale) {
            z /= 4.0L;
        }
        long double r = cabsl(z);
        long double a = cargl(z);
        r = sqrtl(r);
        a /= 2.0;
        long double complex w = CMPLXL(r*cosl(a), r*sinl(a));
        if (scale) {
            w *= 2.0L;
        }
        return w;
    }
}
