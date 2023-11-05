/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <limits.h>
#include <math.h>

double
pow(double x, double y)
{
    /* Annex F exceptions to NaN propagation */
    if (x == 1.0 || y == 0.0) {
        return 1.0;
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
        double xa = fabs(x);
        if (xa < 1.0) {
            return +0.0;
        } else if (xa == 1.0) {
            return +1.0;
        } else {
            return +INFINITY;
        }
    }

    /* Handle y == -inf */
    if (y == -INFINITY) {
        double xa = fabs(x);
        if (xa < 1.0) {
            return +INFINITY;
        } else if (xa == 1.0) {
            return +1.0;
        } else {
            return +0.0;
        }
    }

    /* Handle x == -inf */
    if (x == -INFINITY) {
        double y2 = fmod(y, 2.0);
        if (y2 == -1.0) {
            return -0.0;
        } else if (y2 == +1.0) {
            return -INFINITY;
        } else {
            return signbit(y) ? +0.0 : +INFINITY;
        }
    }

    /* Handle x == +inf */
    if (x == +INFINITY) {
        return signbit(y) ? +0.0 : +INFINITY;
    }

    /* Handle special cases for integer exponent */
    double yi;
    double yf = modf(y, &yi);
    if (yf == 0.0) {
        double ya = fabs(yi);
        if (ya <= ULLONG_MAX) {
            /* Use repeated squaring for small integer exponent */
            unsigned long long yu = (unsigned long long)ya;
            double p = 1.0;
            double xs = x;
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
                if (p == 0.0) {
                    errno = ERANGE;
                }
                p = 1.0 / p;
            }
            return p;
        }
    }

    /* Any case where y is an odd integer is handled above, because the
       precision of unsigned long long exceeds that of double */

    double p;
    if (x == 0.0) {
        p = +0.0;
        if (signbit(y)) {
            errno = ERANGE;
            p = 1.0 / p; /* intentionally raise FE_DIVBYZERO */
        }
    } else if (x == -1.0 && yf == 0.0) {
        p = +1.0;
    } else {
        p = exp(log(x) * y);
    }
    return p;
}
