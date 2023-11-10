/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

float
cargf(float complex z)
{
    return atan2f(__imag__(z), __real__(z));
}
