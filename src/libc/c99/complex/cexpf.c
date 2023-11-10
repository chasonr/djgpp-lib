/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <errno.h>
#include <math.h>

float complex
cexpf(float complex z)
{
    /* ISO/IEC 9899:2018, G.6.3.1 */
    if (isnan(__real__(z))) {
        if (isnan(__imag__(z)) || __imag__(z) == 0.0F) {
            return z;
        } else if (isnan(__imag__(z))) {
            return CMPLXF(__real__(z), __real__(z));
        }
    } else if (__real__(z) == -INFINITY) {
        if (isnan(__imag__(z)) || isinf(__imag__(z))) {
            return CMPLXF(+0.0F, copysignf(0.0F, __imag__(z)));
        }
    } else if (__real__(z) == +INFINITY) {
        if (isnan(__imag__(z)) || __imag__(z) == 0.0F) {
            return z;
        } else if (isinf(__imag__(z))) {
            errno = EDOM;
            return CMPLXF(+INFINITY, 0.0F/0.0F);
        }
    } else if (isnan(__imag__(z))) {
        return CMPLXF(__imag__(z), __imag__(z));
    }

    float r = expf(__real__(z));
    float complex w = CMPLXF(r*cosf(__imag__(z)), r*sinf(__imag__(z)));
    return w;
}
