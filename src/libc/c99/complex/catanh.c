/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

double complex
catanh(double complex z)
{
    /* ISO/IEC 8859:2018 G.6.2.3 */
    if (isnan(__real__(z))) {
        if (isnan(__imag__(z))) {
            return z;
        } else if (isinf(__imag__(z))) {
            return CMPLX(copysign(0.0, __real__(z)),
                         copysign(3.14159265358979323846*0.5, __imag__(z)));
        } else {
            return CMPLX(__real__(z), __real__(z));
        }
    } else if (isinf(__real__(z))) {
        if (isnan(__imag__(z))) {
            return CMPLX(copysign(0.0, __real__(z)), __imag__(z));
        } else {
            return CMPLX(copysign(0.0, __real__(z)),
                         copysign(3.14159265358979323846*0.5, __imag__(z)));
        }
    } else if (isnan(__imag__(z))) {
        if (__real__(z) == 0.0) {
            return z;
        } else {
            return CMPLX(__imag__(z), __imag__(z));
        }
    } else if (isinf(__imag__(z))) {
        return CMPLX(copysign(0.0, __real__(z)),
                     copysign(3.14159265358979323846*0.5, __imag__(z)));
    }

    if (__imag__(z) == 0.0) {
        return CMPLX(atanh(__real__(z)), __imag__(z));
    } else {
        double complex w = 0.5*clog((1.0+z)/(1.0-z));
        return w;
    }
}
