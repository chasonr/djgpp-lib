/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

double
cabs(double complex z)
{
    return hypot(__real__(z), __imag__(z));
}
