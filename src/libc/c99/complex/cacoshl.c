/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

long double complex
cacoshl(long double complex z)
{
    long double x = __real__(z);
    long double y = __imag__(z);

    /* ISO/IEC 9899:2018 G.6.2.1 */
    if (isnan(x)) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLXL(+INFINITY, x);
        } else {
            return CMPLXL(x, x);
        }
    } else if (x == -INFINITY) {
        if (isnan(y)) {
            return CMPLXL(+INFINITY, y);
        } else if (isinf(y)) {
            return CMPLXL(+INFINITY, copysignl(3.14159265358979323846L*0.75L, y));
        } else {
            return CMPLXL(+INFINITY, copysignl(3.14159265358979323846L, y));
        }
    } else if (x == +INFINITY) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLXL(+INFINITY, copysignl(3.14159265358979323846L*0.25L, y));
        } else {
            return CMPLXL(+INFINITY, copysignl(0.0L, y));
        }
    } else if (isnan(y)) {
        if (x == 0.0L) {
            return CMPLXL(y, +3.14159265358979323846L*0.5L);
        } else {
            return CMPLXL(y, y);
        }
    } else if (isinf(y)) {
        return CMPLXL(+INFINITY, copysignl(+3.14159265358979323846L*0.5L, y));
    }

    if (y == 0.0L) {
        if (x < -1.0L) {
            return CMPLXL(acoshl(-x),
                          copysignl(+3.14159265358979323846L, y));
        } else if (x <= +1.0L) {
            return CMPLXL(+0.0L, copysignl(acosl(x), y));
        } else {
            return CMPLXL(acoshl(+x), y);
        }
    } else {
        long double complex w;
        if (fabsl(x) > 1e18L || fabsl(y) > 1e18L) {
            /* z*z + 1 == z within machine precision; avoid premature
               overflow */
            w = clogl(z) + 0.693147180559945309417L;
        } else {
            w = clogl(z + csqrtl(z + 1.0L)*csqrtl(z - 1.0L));
        }
        /* Deal with cancellations */
        w -= (ccoshl(w) - z)/csinhl(w);
        if (signbit(x)) {
            w = -w;
        }
        return w;
    }
}
