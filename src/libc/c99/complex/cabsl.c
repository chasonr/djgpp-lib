/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

long double
cabsl(long double complex z)
{
    return hypotl(__real__(z), __imag__(z));
}
