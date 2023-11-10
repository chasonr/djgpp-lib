/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

float complex
cacoshf(float complex z)
{
    float x = __real__(z);
    float y = __imag__(z);

    /* ISO/IEC 9899:2018 G.6.2.1 */
    if (isnan(x)) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLXF(+INFINITY, x);
        } else {
            return CMPLXF(x, x);
        }
    } else if (x == -INFINITY) {
        if (isnan(y)) {
            return CMPLXF(+INFINITY, y);
        } else if (isinf(y)) {
            return CMPLXF(+INFINITY, copysignf(3.14159265358979323846F*0.75F, y));
        } else {
            return CMPLXF(+INFINITY, copysignf(3.14159265358979323846F, y));
        }
    } else if (x == +INFINITY) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLXF(+INFINITY, copysignf(3.14159265358979323846F*0.25F, y));
        } else {
            return CMPLXF(+INFINITY, copysignf(0.0F, y));
        }
    } else if (isnan(y)) {
        if (x == 0.0F) {
            return CMPLXF(y, +3.14159265358979323846F*0.5F);
        } else {
            return CMPLXF(y, y);
        }
    } else if (isinf(y)) {
        return CMPLXF(+INFINITY, copysignf(+3.14159265358979323846F*0.5F, y));
    }

    if (y == 0.0F) {
        if (x < -1.0F) {
            return CMPLXF(acoshf(-x),
                          copysignf(+3.14159265358979323846F, y));
        } else if (x <= +1.0F) {
            return CMPLXF(+0.0F, copysignf(acosf(x), y));
        } else {
            return CMPLXF(acoshf(+x), y);
        }
    } else {
        float complex w;
        if (fabsf(x) > 1e18F || fabsf(y) > 1e18F) {
            /* z*z + 1 == z within machine precision; avoid premature
               overflow */
            w = clogf(z) + 0.693147180559945309417F;
        } else {
            w = clogf(z + csqrtf(z + 1.0F)*csqrtf(z - 1.0F));
        }
        /* Deal with cancellations */
        w -= (ccoshf(w) - z)/csinhf(w);
        if (signbit(x)) {
            w = -w;
        }
        return w;
    }
}
