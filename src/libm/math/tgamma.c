/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>
#include "fdlibm.h"

double
tgamma(double x)
{
    int sign;

    if (_LIB_VERSION == _IEEE_) {
        if (isnan(x) || x == +HUGE_VAL) {
            return x;
        }
        if (x == 0.0) {
            return 1.0 / x;
        }
        if (x == -HUGE_VAL || (x < 0.0 && floorf(x) == x)) {
            return 0.0 / 0.0;
        }
    }

    double y = exp(__ieee754_lgamma_r(x, &sign));
    if (sign) {
        y = -y;
    }
    return y;
}
