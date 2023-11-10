/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

long double complex
ccosl(long double complex z)
{
    /* ISO/IEC 9899:2018, G.6 paragraph 7 */
    long double complex zi = CMPLXL(-__imag__(z), +__real__(z));
    long double complex w = ccoshl(zi);
    return w;
}
