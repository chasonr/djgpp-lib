/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <limits.h>
#include <math.h>

long
lroundl(long double x)
{
    long double yf = roundl(x);

    if (yf < LONG_MIN || LONG_MAX < yf) {
        errno = ERANGE;
    }

    long y = (long)yf;
    return y;
}
