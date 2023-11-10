/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

double
carg(double complex z)
{
    return atan2(__imag__(z), __real__(z));
}
