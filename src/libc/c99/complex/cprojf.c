/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

float complex
cprojf(float complex z)
{
    if (isinf(__real__(z)) || isinf(__imag__(z))) {
        return CMPLXF(INFINITY, 0.0F);
    } else {
        return z;
    }
}
