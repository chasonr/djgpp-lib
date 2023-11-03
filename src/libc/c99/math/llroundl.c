/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <errno.h>
#include <limits.h>
#include <math.h>

long long
llroundl(long double x)
{
    long double yf = roundl(x);

    if (yf < LLONG_MIN || LLONG_MAX < yf) {
        errno = ERANGE;
    }

    long long y = (long long)yf;
    return y;
}
