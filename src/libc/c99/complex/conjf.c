/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

float complex
conjf(float complex z)
{
    return CMPLXF(__real__(z), -__imag__(z));
}
