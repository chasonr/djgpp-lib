/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <errno.h>
#include <math.h>

long double complex
cexpl(long double complex z)
{
    /* ISO/IEC 9899:2018, G.6.3.1 */
    if (isnan(__real__(z))) {
        if (isnan(__imag__(z)) || __imag__(z) == 0.0) {
            return z;
        } else if (isnan(__imag__(z))) {
            return CMPLXL(__real__(z), __real__(z));
        }
    } else if (__real__(z) == -INFINITY) {
        if (isnan(__imag__(z)) || isinf(__imag__(z))) {
            return CMPLXL(+0.0, copysign(0.0, __imag__(z)));
        }
    } else if (__real__(z) == +INFINITY) {
        if (isnan(__imag__(z)) || __imag__(z) == 0.0) {
            return z;
        } else if (isinf(__imag__(z))) {
            errno = EDOM;
            return CMPLXL(+INFINITY, 0.0/0.0);
        }
    } else if (isnan(__imag__(z))) {
        return CMPLXL(__imag__(z), __imag__(z));
    }

    long double r = expl(__real__(z));
    long double complex w = CMPLXL(r*cosl(__imag__(z)), r*sinl(__imag__(z)));
    return w;
}
