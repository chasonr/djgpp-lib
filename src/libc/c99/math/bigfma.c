/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <fenv.h>
#include <math.h>
#include "bigfma.h"

// Double-double algorithms adapted from the QD package, available at
// https://www.davidhbailey.com/dhbsoftware/
static void dd_add(const long double a[2], long double b, long double sum[3]);
static long double two_prod(long double a, long double b, long double *err);
static void renorm(long double *c0, long double *c1, long double *c2);
static long double quick_two_sum(long double a, long double b, long double *err);
static void split(long double a, long double *hi, long double *lo);

void __dj_big_fma(
        long double x, long double y, long double z,
        long double sum[3])
{
    long double prod[2];

    int round = fegetround();
    fesetround(FE_TONEAREST);

    prod[0] = two_prod(x, y, &prod[1]);
    if (isfinite(prod[0])) {
        dd_add(prod, z, sum);
    } else {
        sum[0] = prod[0];
        sum[1] = 0.0L;
        sum[2] = 0.0L;
    }

    fesetround(round);
}

static void
dd_add(const long double a[2], long double b, long double sum[3])
{
    long double c0, c1, c2;
    long double e;

    c0 = __dj_two_sum(a[0], b, &e);
    c1 = __dj_two_sum(a[1], e, &c2);

    renorm(&c0, &c1, &c2);

    sum[0] = c0;
    sum[1] = c1;
    sum[2] = c2;
}

/* Computes fl(a*b) and err(a*b). */
static long double
two_prod(long double a, long double b, long double *err)
{
    long double a_hi, a_lo, b_hi, b_lo;
    long double p = a * b;
    if (isfinite(p)) {
        split(a, &a_hi, &a_lo);
        split(b, &b_hi, &b_lo);
        *err = ((a_hi * b_hi - p) + a_hi * b_lo + a_lo * b_hi) + a_lo * b_lo;
    } else {
        *err = 0.0L;
    }
    return p;
}

static void
renorm(long double *c0, long double *c1, long double *c2)
{
    long double s0, s1, s2 = 0.0;

    if (!isfinite(*c0)) return;

    s0  = *c2;
    s0  = quick_two_sum(*c1, s0, c2);
    *c0 = quick_two_sum(*c0, s0, c1);

    s0 = *c0;
    s1 = *c1;
    if (s1 != 0.0) {
        s1 = quick_two_sum(s1, *c2, &s2);
    } else {
        s0 = quick_two_sum(s0, *c2, &s1);
    }

    *c0 = s0;
    *c1 = s1;
    *c2 = s2;
}

/* Computes fl(a+b) and err(a+b).  Assumes |a| >= |b|. */
static long double
quick_two_sum(long double a, long double b, long double *err)
{
  long double s = a + b;
  *err = b - (s - a);
  return s;
}

/* Computes high word and lo word of a */
static void
split(long double a, long double *hi, long double *lo)
{
    static const long double _QD_SPLITTER = 0x1.0P+32L + 1.0L;
    static const long double _QD_SPLIT_THRESH = 0x1.0P+992;
    static const long double scale_down = 0x1.0P-32;
    static const long double scale_up = 0x1.0P+32;

    long double temp;
    if (a >= _QD_SPLIT_THRESH || a <= -_QD_SPLIT_THRESH) {
        a *= scale_down;
        temp = _QD_SPLITTER * a;
        *hi = temp - (temp - a);
        *lo = a - *hi;
        *hi *= scale_up;
        *lo *= scale_up;
    } else {
        temp = _QD_SPLITTER * a;
        *hi = temp - (temp - a);
        *lo = a - *hi;
    }
}
