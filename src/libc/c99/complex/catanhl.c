/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

long double complex
catanhl(long double complex z)
{
    /* ISO/IEC 8859:2018 G.6.2.3 */
    if (isnan(__real__(z))) {
        if (isnan(__imag__(z))) {
            return z;
        } else if (isinf(__imag__(z))) {
            return CMPLXL(copysignl(0.0L, __real__(z)),
                          copysignl(3.14159265358979323846L*0.5L, __imag__(z)));
        } else {
            return CMPLXL(__real__(z), __real__(z));
        }
    } else if (isinf(__real__(z))) {
        if (isnan(__imag__(z))) {
            return CMPLXL(copysignl(0.0L, __real__(z)), __imag__(z));
        } else {
            return CMPLXL(copysignl(0.0L, __real__(z)),
                          copysignl(3.14159265358979323846L*0.5L, __imag__(z)));
        }
    } else if (isnan(__imag__(z))) {
        if (__real__(z) == 0.0L) {
            return z;
        } else {
            return CMPLXL(__imag__(z), __imag__(z));
        }
    } else if (isinf(__imag__(z))) {
        return CMPLXL(copysignl(0.0L, __real__(z)),
                      copysignl(3.14159265358979323846L*0.5L, __imag__(z)));
    }

    if (__imag__(z) == 0.0L) {
        return CMPLXL(atanhl(__real__(z)), __imag__(z));
    } else {
        long double complex w = 0.5L*clogl((1.0L+z)/(1.0L-z));
        return w;
    }
}
