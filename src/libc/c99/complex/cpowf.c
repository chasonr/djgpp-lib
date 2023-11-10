/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

float complex
cpowf(float complex x, float complex y)
{
    return cexpf(clogf(x) * y);
}
