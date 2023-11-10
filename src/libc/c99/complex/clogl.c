/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

long double complex
clogl(long double complex z)
{
    long double complex w = CMPLXL(logl(cabsl(z)), cargl(z));
    return w;
}
