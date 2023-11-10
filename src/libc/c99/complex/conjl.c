/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

long double complex
conjl(long double complex z)
{
    return CMPLXL(__real__(z), -__imag__(z));
}
