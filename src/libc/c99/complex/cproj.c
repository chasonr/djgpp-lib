/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

double complex
cproj(double complex z)
{
    if (isinf(__real__(z)) || isinf(__imag__(z))) {
        return CMPLX(INFINITY, 0.0);
    } else {
        return z;
    }
}
