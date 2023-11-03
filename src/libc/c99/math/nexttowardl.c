/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

long double
nexttowardl(long double x, long double y)
{
    return nextafterl(x, y);
}
