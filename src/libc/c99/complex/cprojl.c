/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

long double complex
cprojl(long double complex z)
{
    if (isinf(__real__(z)) || isinf(__imag__(z))) {
        return CMPLXL(INFINITY, 0.0L);
    } else {
        return z;
    }
}
