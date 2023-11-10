/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <errno.h>
#include <math.h>

float complex
ccoshf(float complex z)
{
    float x = __real__(z);
    float y = __imag__(z);

    /* ISO/IEC 9899:2018 G6.2.4 */
    if (isnan(x)) {
        if (isnan(y) || y == 0.0F) {
            return z;
        } else {
            return CMPLXF(x, x);
        }
    } else if (isinf(x)) {
        if (isnan(y) || y == 0.0F) {
            return CMPLXF(INFINITY, signbit(x) ? -y : +y);
        } else if (isinf(y)) {
            errno = EDOM;
            return CMPLXF(INFINITY, 0.0F/0.0F);
        }
    } else if (isnan(y)) {
        if (x == 0.0F) {
            return CMPLXF(y, x);
        } else {
            return CMPLXF(y, y);
        }
    } else if (isinf(y) && x == 0.0F) {
        errno = EDOM;
        return CMPLXF(0.0F/0.0F, signbit(y) ? -x : +x);
    }

    float cx = coshf(x);
    float sx = sinhf(x);
    float cy = cosf(y);
    float sy = sinf(y);
    return CMPLXF(cx*cy, sx*sy);
}
