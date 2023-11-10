/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>
#include <stdbool.h>

long double complex
casinhl(long double complex z)
{
    double x = __real__(z);
    double y = __imag__(z);

    /* ISO/IEC 8859:2018 G.6.2.2 */
    if (isnan(x)) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLXL(y, x);
        }
    } else if (isinf(x)) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLXL(x, copysignl(3.14159265358979323846L*0.25L, y));
        } else {
            return CMPLXL(x, copysignl(0.0L, y));
        }
    } else if (isinf(y)) {
        return CMPLXL(copysignl(INFINITY, x),
                      copysignl(3.14159265358979323846L*0.5L, y));
    }

    if (y == 0.0L) {
        return CMPLXL(asinhl(x), y);
    } else {
        bool neg = signbit(x);
        long double complex za = neg ? -z : +z;
        long double complex wa;
        if (fabsl(x) > 1e18L || fabsl(y) > 1e18L) {
            /* za*za + 1 == za within machine precision; avoid premature
               overflow */
            wa = clogl(za) + 0.693147180559945309417L;
        } else {
            wa = clogl(za + csqrtl(za*za + 1.0L));
        }
        long double complex w = neg ? -wa : +wa;
        return w;
    }
}
