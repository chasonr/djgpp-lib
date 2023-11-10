/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

long double
creall(long double complex z)
{
    return __real__(z);
}
