/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

double complex
ccos(double complex z)
{
    /* ISO/IEC 9899:2018, G.6 paragraph 7 */
    double complex zi = CMPLX(-__imag__(z), +__real__(z));
    double complex w = ccosh(zi);
    return w;
}
