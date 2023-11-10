/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

float
cabsf(float complex z)
{
    return hypotf(__real__(z), __imag__(z));
}
