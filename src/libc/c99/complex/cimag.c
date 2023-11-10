/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

double
cimag(double complex z)
{
    return __imag__(z);
}
