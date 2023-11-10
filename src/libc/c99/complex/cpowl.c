/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <complex.h>
#include <math.h>

long double complex
cpowl(long double complex x, long double complex y)
{
    return cexpl(clogl(x) * y);
}
