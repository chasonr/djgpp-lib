/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

float complex
catanhf(float complex z)
{
    /* ISO/IEC 8859:2018 G.6.2.3 */
    if (isnan(__real__(z))) {
        if (isnan(__imag__(z))) {
            return z;
        } else if (isinf(__imag__(z))) {
            return CMPLXF(copysignf(0.0F, __real__(z)),
                          copysignf(3.14159265358979323846F*0.5F, __imag__(z)));
        } else {
            return CMPLXF(__real__(z), __real__(z));
        }
    } else if (isinf(__real__(z))) {
        if (isnan(__imag__(z))) {
            return CMPLXF(copysignf(0.0F, __real__(z)), __imag__(z));
        } else {
            return CMPLXF(copysignf(0.0F, __real__(z)),
                          copysignf(3.14159265358979323846F*0.5F, __imag__(z)));
        }
    } else if (isnan(__imag__(z))) {
        if (__real__(z) == 0.0F) {
            return z;
        } else {
            return CMPLXF(__imag__(z), __imag__(z));
        }
    } else if (isinf(__imag__(z))) {
        return CMPLXF(copysignf(0.0F, __real__(z)),
                      copysignf(3.14159265358979323846F*0.5F, __imag__(z)));
    }

    if (__imag__(z) == 0.0F) {
        return CMPLXF(atanhf(__real__(z)), __imag__(z));
    } else {
        float complex w = 0.5F*clogf((1.0F+z)/(1.0F-z));
        return w;
    }
}
