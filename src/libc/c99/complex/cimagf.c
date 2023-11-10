/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

float
cimagf(float complex z)
{
    return __imag__(z);
}
