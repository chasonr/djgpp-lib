/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

double complex
cacos(double complex z)
{
    /* ISO/IEC 9899:2018 G.6.2.1 */
    if (isnan(__real__(z)) && isinf(__imag__(z))) {
        return conj(z);
    }

    double complex wi = cacosh(z);
    double complex w = CMPLX(-__imag__(wi), +__real__(wi));
    if (signbit(__real__(w)) && !isnan(__real__(w))) {
        w = -w;
    }
    return w;
}
