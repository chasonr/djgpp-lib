/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdint.h>

static long double increment(long double x);
static long double decrement(long double x);

long double
nextafterl(long double x, long double y)
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
    if (x == 0.0L) {
        x = copysignl(0.0L, y);
    }

    /* Bump x in the direction of y */
    long double result;

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
    } else if (fabsl(result) < LDBL_MIN) {
        errno = ERANGE;
        feraiseexcept(FE_UNDERFLOW | FE_INEXACT);
    }

    return result;
}

static long double
increment(long double x)
{
    union {
        long double f;
        uint32_t i[3];
    } u;

    u.f = x;
    u.i[2] &= 0xFFFF;
    ++u.i[0];
    if (u.i[0] == 0) {
        ++u.i[1];
        if (u.i[1] == 0) {
            ++u.i[2];
        }
    }
    /* Skip past unsupported formats */
    if ((u.i[2] & 0x7FFF) == 0) {
        if ((u.i[1] & 0x80000000) != 0) {
            u.i[2] |= 0x0001;
        }
    } else {
        u.i[1] |= 0x80000000;
    }
    return u.f;
}

static long double
decrement(long double x)
{
    union {
        long double f;
        uint32_t i[3];
    } u;

    u.f = x;
    u.i[2] &= 0xFFFF;
    if (u.i[0] == 0) {
        if (u.i[1] == 0) {
            --u.i[2];
        }
        --u.i[1];
    }
    --u.i[0];
    /* Skip past unsupported formats */
    if (u.i[1] == 0x7FFFFFFF && (u.i[2] & 0x7FFF) != 0) {
        --u.i[2];
        if ((u.i[2] & 0x7FFF) != 0) {
            u.i[1] |= 0x80000000;
        }
    } else if ((u.i[2] & 0x7FFF) == 0) {
        u.i[1] &= 0x7FFFFFFF;
    }
    return u.f;
}
