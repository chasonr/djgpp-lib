/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

long double
roundl(long double x)
{
    long double y;

    if (signbit(x)) {
        y = ceill(x - 0.5L);
    } else {
        y = floorl(x + 0.5L);
    }
    return y;
}
