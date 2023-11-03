/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <fenv.h>
#include <math.h>

long double
nearbyintl(long double x)
{
    /* nearbyintl differs from rintl only in that it is not allowed to raise
       the FE_INEXACT exception. */

    fenv_t fenv;
    feholdexcept(&fenv);

    long double y = rintf(x);

    feclearexcept(FE_INEXACT);
    feupdateenv(&fenv);

    return y;
}
