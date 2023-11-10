/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

float complex
cacosf(float complex z)
{
    /* ISO/IEC 9899:2018 G.6.2.1 */
    if (isnan(__real__(z)) && isinf(__imag__(z))) {
        return conjf(z);
    }

    float complex wi = cacoshf(z);
    float complex w = CMPLXF(-__imag__(wi), +__real__(wi));
    if (signbit(__real__(w)) && !isnan(__real__(w))) {
        w = -w;
    }
    return w;
}
