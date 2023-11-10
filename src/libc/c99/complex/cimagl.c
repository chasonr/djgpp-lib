/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

long double
cimagl(long double complex z)
{
    return __imag__(z);
}
