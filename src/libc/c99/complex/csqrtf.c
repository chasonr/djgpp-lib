/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>
#include <stdbool.h>

float complex
csqrtf(float complex z)
{
    /* ISO/IEC 9899:2018, G.6.4.2 */
    if (isnan(__imag__(z))) {
        if (isnan(__real__(z)) || __real__(z) == +INFINITY) {
            return z;
        } else if (__real__(z) == -INFINITY) {
            return CMPLXF(__imag__(z), copysignf(INFINITY, __imag__(z)));
        } else {
            return CMPLXF(__imag__(z), __imag__(z));
        }
    }
    if (isinf(__imag__(z))) {
        return CMPLXF(INFINITY, __imag__(z)); /* even if __real__(z) is NaN */
    }
    if (isnan(__real__(z))) {
        return CMPLXF(__real__(z), __real__(z));
    }
    if (__real__(z) == +INFINITY) {
        return CMPLXF(+INFINITY, copysignf(0.0F, __imag__(z)));
    }
    if (__real__(z) == -INFINITY) {
        return CMPLXF(0.0F, copysignf(INFINITY, __imag__(z)));
    }

    if (__imag__(z) == 0.0F) {
        float w = sqrtf(fabsf(__real__(z)));
        if (signbit(__real__(z))) {
            return CMPLXF(0.0F, copysignf(w, __imag__(z)));
        } else {
            return CMPLXF(w, __imag__(z));
        }
    } else {
        /* Avoid overflow in cabsf */
        bool scale = fabsf(__real__(z)) > 1e36F || fabsf(__imag__(z)) > 1e36F;
        if (scale) {
            z /= 4.0F;
        }
        float r = cabsf(z);
        float a = cargf(z);
        r = sqrtf(r);
        a /= 2.0F;
        float complex w = CMPLXF(r*cosf(a), r*sinf(a));
        if (scale) {
            w *= 2.0F;
        }
        return w;
    }
}
