/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

double complex
conj(double complex z)
{
    return CMPLX(__real__(z), -__imag__(z));
}
