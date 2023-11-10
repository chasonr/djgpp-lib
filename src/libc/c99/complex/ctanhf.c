/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>

float complex
ctanhf(float complex z)
{
    float x = __real__(z);
    float y = __imag__(z);

    /* ISO/IEC 9899:2018 G6.2.6 */
    if (isnan(x)) {
        if (isnan(y) || y == 0.0F) {
            return z;
        }
    } else if (isinf(x)) {
        if (isnan(y) || isinf(y)) {
            return CMPLXF(copysignf(1.0F, x), copysignf(0.0F, y));
        } else {
            return CMPLXF(copysignf(1.0F, x), copysignf(0.0F, sinf(2.0F*y)));
        }
    } else if (isnan(y)) {
        if (x == 0.0F) {
            return z;
        } else {
            return CMPLXF(y, y);
        }
    } else if (isinf(y)) {
        errno = EDOM;
        if (x == 0.0F) {
            return CMPLXF(x, 0.0F/0.0F);
        } else {
            return CMPLXF(NAN, 0.0F/0.0F);
        }
    }

    bool neg = signbit(x);
    if (neg) {
        x = -x;
        y = -y;
    }

    float e2m = expf(-2.0F*x);
    float e2m1 = -expm1f(-2.0F*x);

    float complex w = CMPLXF(e2m1*(1.0F+e2m), 2.0F*e2m*sinf(2.0F*y))
                    / (1.0F + 2.0F*e2m*cosf(2.0F*y) + e2m*e2m);

    if (neg) {
        w = -w;
    }

    return w;
}
