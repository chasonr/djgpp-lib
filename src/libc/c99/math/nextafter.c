/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdint.h>

static double increment(double x);
static double decrement(double x);

double
nextafter(double x, double y)
{
    /* Propagate NaNs */
    if (isnan(x)) {
        return x;
    }
    if (isnan(y)) {
        return y;
    }

    /* Handle case where x == y; consider sign of zero */
    if (x == y) {
        /* If x == 0 and y == 0, use the sign of y */
        return y;
    }

    /* Otherwise, if x == 0, give it the sign of y */
    if (x == 0.0) {
        x = copysign(0.0, y);
    }

    /* Bump x in the direction of y */
    double result;

    if (x < y) {
        if (signbit(x)) {
            result = decrement(x);
        } else {
            result = increment(x);
        }
    } else {
        if (signbit(x)) {
            result = increment(x);
        } else {
            result = decrement(x);
        }
    }

    /* Raise exceptions specified in Annex F */

    if (isinf(result)) {
        errno = ERANGE;
        feraiseexcept(FE_OVERFLOW | FE_INEXACT);
    } else if (fabs(result) < DBL_MIN) {
        errno = ERANGE;
        feraiseexcept(FE_UNDERFLOW | FE_INEXACT);
    }

    return result;
}

static double
increment(double x)
{
    union {
        double f;
        uint64_t i;
    } u;

    u.f = x;
    ++u.i;
    return u.f;
}

static double
decrement(double x)
{
    union {
        double f;
        uint64_t i;
    } u;

    u.f = x;
    --u.i;
    return u.f;
}
