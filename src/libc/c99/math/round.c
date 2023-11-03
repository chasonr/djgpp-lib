/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

double
round(double x)
{
    double y;

    if (signbit(x)) {
        y = ceil(x - 0.5L);
    } else {
        y = floor(x + 0.5L);
    }
    return y;
}
