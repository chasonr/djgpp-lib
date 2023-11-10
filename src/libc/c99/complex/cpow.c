/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

double complex
cpow(double complex x, double complex y)
{
    return cexp(clog(x) * y);
}
