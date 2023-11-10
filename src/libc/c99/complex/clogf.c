/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

float complex
clogf(float complex z)
{
    double complex w = CMPLXF(logf(cabsf(z)), cargf(z));
    return w;
}
