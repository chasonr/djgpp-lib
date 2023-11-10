/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>

float complex
csinf(float complex z)
{
    /* ISO/IEC 9899:2018, G.6 paragraph 7 */
    float complex zi = CMPLXF(-__imag__(z), +__real__(z));
    float complex wi = csinhf(zi);
    float complex w = CMPLXF(+__imag__(wi), -__real__(wi));
    return w;
}
