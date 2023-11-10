/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>
#include <stdbool.h>

float complex
casinhf(float complex z)
{
    double x = __real__(z);
    double y = __imag__(z);

    /* ISO/IEC 8859:2018 G.6.2.2 */
    if (isnan(x)) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLXF(y, x);
        }
    } else if (isinf(x)) {
        if (isnan(y)) {
            return z;
        } else if (isinf(y)) {
            return CMPLXF(x, copysignf(3.14159265358979323846F*0.25F, y));
        } else {
            return CMPLXF(x, copysignf(0.0F, y));
        }
    } else if (isinf(y)) {
        return CMPLXF(copysignf(INFINITY, x),
                      copysignf(3.14159265358979323846F*0.5F, y));
    }

    if (y == 0.0F) {
        return CMPLXF(asinhf(x), y);
    } else {
        bool neg = signbit(x);
        float complex za = neg ? -z : +z;
        float complex wa;
        if (fabsf(x) > 1e18F || fabsf(y) > 1e18F) {
            /* za*za + 1 == za within machine precision; avoid premature
               overflow */
            wa = clogf(za) + 0.693147180559945309417F;
        } else {
            wa = clogf(za + csqrtf(za*za + 1.0F));
        }
        float complex w = neg ? -wa : +wa;
        return w;
    }
}
