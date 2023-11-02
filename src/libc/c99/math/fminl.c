/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

long double
fminl(long double x, long double y)
{
    return (islessequal(x, y) || isnan(y)) ? x : y;
}
