/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

long double complex
csinl(long double complex z)
{
    /* ISO/IEC 9899:2018, G.6 paragraph 7 */
    long double complex zi = CMPLXL(-__imag__(z), +__real__(z));
    long double complex wi = csinhl(zi);
    long double complex w = CMPLXL(+__imag__(wi), -__real__(wi));
    return w;
}
