/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>

double
scalbn(double x, int exp)
{
    return ldexp(x, exp);
}
