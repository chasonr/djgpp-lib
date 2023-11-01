/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include "bigfma.h"

// Double-double algorithms adapted from the QD package, available at
// https://www.davidhbailey.com/dhbsoftware/

/* Computes fl(a+b) and err(a+b).  */
long double
__dj_two_sum(long double a, long double b, long double *err)
{
    long double s = a + b;
    long double bb = s - a;
    *err = (a - (s - bb)) + (b - bb);
    return s;
}
