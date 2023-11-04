/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <limits.h>
#include <math.h>

float
powf(float x, float y)
{
    /* Annex F exceptions to NaN propagation */
    if (x == 1.0F || y == 0.0F) {
        return 1.0F;
    }

    /* Propagate NaNs */
    if (isnan(x)) {
        return x;
    }
    if (isnan(y)) {
        return y;
    }

    /* Handle y == +inf */
    if (y == +INFINITY) {
        float xa = fabsf(x);
        if (xa < 1.0F) {
            return +0.0F;
        } else if (xa == 1.0F) {
            return +1.0F;
        } else {
            return +INFINITY;
        }
    }

    /* Handle y == -inf */
    if (y == -INFINITY) {
        float xa = fabsf(x);
        if (xa < 1.0F) {
            return +INFINITY;
        } else if (xa == 1.0F) {
            return +1.0F;
        } else {
            return +0.0F;
        }
    }

    /* Handle x == -inf */
    if (x == -INFINITY) {
        float y2 = fmodf(y, 2.0F);
        if (y2 == -1.0F) {
            return -0.0F;
        } else if (y2 == +1.0F) {
            return -INFINITY;
        } else {
            return signbit(y) ? +0.0F : +INFINITY;
        }
    }

    /* Handle x == +inf */
    if (x == +INFINITY) {
        return signbit(y) ? +0.0F : +INFINITY;
    }

    /* Handle special cases for integer exponent */
    float yi;
    float yf = modff(y, &yi);
    if (yf == 0.0F) {
        float ya = fabsf(yi);
        if (ya <= ULONG_MAX) {
            /* Use repeated squaring for small integer exponent */
            unsigned long yu = (unsigned long)ya;
            float p = 1.0F;
            float xs = x;
            while (yu != 0U) {
                if ((yu & 1) != 0) {
                    p *= xs;
                }
                yu >>= 1;
                if (yu != 0U) {
                    xs *= xs;
                }
            }
            if (signbit(y)) {
                if (p == 0.0F) {
                    errno = ERANGE;
                }
                p = 1.0F / p;
            }
            return p;
        }
    }

    /* Any case where y is an odd integer is handled above, because the
       precision of unsigned long exceeds that of float */

    float p;
    if (x == 0.0F) {
        p = +0.0F;
        if (signbit(y)) {
            errno = ERANGE;
            p = 1.0F / p; /* intentionally raise FE_DIVBYZERO */
        }
    } else if (x == -1.0F && yf == 0.0F) {
        p = +1.0F;
    } else {
        p = expf(logf(x) * y);
    }
    return p;
}
