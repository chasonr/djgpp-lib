/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

float
crealf(float complex z)
{
    return __real__(z);
}
