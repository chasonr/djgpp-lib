/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

long double
cargl(long double complex z)
{
    return atan2l(__imag__(z), __real__(z));
}
