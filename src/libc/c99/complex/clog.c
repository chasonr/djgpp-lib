/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

double complex
clog(double complex z)
{
    double complex w = CMPLX(log(cabs(z)), carg(z));
    return w;
}
