/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <errno.h>
#include <math.h>

double complex
cexp(double complex z)
{
    /* ISO/IEC 9899:2018, G.6.3.1 */
    if (isnan(__real__(z))) {
        if (isnan(__imag__(z)) || __imag__(z) == 0.0L) {
            return z;
        } else if (isnan(__imag__(z))) {
            return CMPLX(__real__(z), __real__(z));
        }
    } else if (__real__(z) == -INFINITY) {
        if (isnan(__imag__(z)) || isinf(__imag__(z))) {
            return CMPLX(+0.0L, copysignl(0.0L, __imag__(z)));
        }
    } else if (__real__(z) == +INFINITY) {
        if (isnan(__imag__(z)) || __imag__(z) == 0.0L) {
            return z;
        } else if (isinf(__imag__(z))) {
            errno = EDOM;
            return CMPLX(+INFINITY, 0.0L/0.0L);
        }
    } else if (isnan(__imag__(z))) {
        return CMPLX(__imag__(z), __imag__(z));
    }

    double r = exp(__real__(z));
    double complex w = CMPLX(r*cos(__imag__(z)), r*sin(__imag__(z)));
    return w;
}
