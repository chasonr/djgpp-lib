/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <math.h>
#include "fdlibm.h"

float
tgammaf(float x)
{
    int sign;

    if (_LIB_VERSION == _IEEE_) {
        if (isnan(x) || x == +HUGE_VAL) {
            return x;
        }
        if (x == 0.0F) {
            return 1.0F / x;
        }
        if (x == -HUGE_VAL || (x < 0.0F && floorf(x) == x)) {
            return 0.0F / 0.0F;
        }
    }

    float y = expf(__ieee754_lgammaf_r(x, &sign));
    if (sign) {
        y = -y;
    }
    return y;
}
