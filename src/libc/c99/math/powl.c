/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <limits.h>
#include <math.h>

long double
powl(long double x, long double y)
{
    /* Annex F exceptions to NaN propagation */
    if (x == 1.0L || y == 0.0L) {
        return 1.0L;
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
        long double xa = fabsl(x);
        if (xa < 1.0L) {
            return +0.0L;
        } else if (xa == 1.0L) {
            return +1.0L;
        } else {
            return +INFINITY;
        }
    }

    /* Handle y == -inf */
    if (y == -INFINITY) {
        long double xa = fabsl(x);
        if (xa < 1.0L) {
            return +INFINITY;
        } else if (xa == 1.0L) {
            return +1.0L;
        } else {
            return +0.0L;
        }
    }

    /* Handle x == -inf */
    if (x == -INFINITY) {
        long double y2 = fmodl(y, 2.0L);
        if (y2 == -1.0L) {
            return -0.0L;
        } else if (y2 == +1.0L) {
            return -INFINITY;
        } else {
            return signbit(y) ? +0.0L : +INFINITY;
        }
    }

    /* Handle x == +inf */
    if (x == +INFINITY) {
        return signbit(y) ? +0.0L : +INFINITY;
    }

    /* Handle special cases for integer exponent */
    long double yi;
    long double yf = modfl(y, &yi);
    if (yf == 0.0L) {
        long double ya = fabsl(yi);
        if (ya <= ULLONG_MAX) {
            /* Use repeated squaring for small integer exponent */
            unsigned long long yu = (unsigned long long)ya;
            long double p = 1.0L;
            long double xs = x;
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
                if (p == 0.0L) {
                    errno = ERANGE;
                }
                p = 1.0L / p;
            }
            return p;
        }
    }

    /* Any case where y is an odd integer is handled above, because the
       precision of unsigned long long equals that of long double */

    long double p;
    if (x == 0.0L) {
        p = +0.0L;
        if (signbit(y)) {
            errno = ERANGE;
            p = 1.0L / p; /* intentionally raise FE_DIVBYZERO */
        }
    } else if (x == -1.0L && yf == 0.0L) {
        p = +1.0L;
    } else {
        p = expl(logl(x) * y);
    }
    return p;
}

