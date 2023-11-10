/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

double
creal(double complex z)
{
    return __real__(z);
}
