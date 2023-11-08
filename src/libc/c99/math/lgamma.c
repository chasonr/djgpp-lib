/*
 * Converted from nswclibr.f, a public domain work of the United States
 * Government, available at https://dev.aao.org.au/rds/nswc among other
 * places.
 * Conversion by Ray Chason, 2023.
 * Comments are as in the original code. Changes are made for Annex F
 * conformance.
 */

#include <math.h>
#include "dgam1.h"

static double dgamln(double x);
static double dgmln1(double x);

double
lgamma(double a)
{
    static const double pi = 3.14159265358979323846264338327950;

    if (isnan(a)) {
        return a;
    } else if (a >= 0.0) {
        return dgamln(a);
    } else {
        if (isinf(a)) {
            return HUGE_VAL;
        } else if (fmod(a, 1.0) == 0.0) {
            return 1.0/0.0;
        } else {
            double prod = pi/__dj_dsin1(a);
            return log(fabs(prod)) - dgamln(1.0 - a);
        }
    }
}

static double
dgamln(double a)
{
//-----------------------------------------------------------------------
//
//           EVALUATION OF LN(GAMMA(A)) FOR POSITIVE A
//
//-----------------------------------------------------------------------
//     WRITTEN BY ALFRED H. MORRIS
//          NAVAL SURFACE WEAPONS CENTER
//          DAHLGREN, VIRGINIA
//-----------------------------------------------------------------------
//     D = 0.5*(LN(2*PI) - 1)
//-----------------------------------------------------------------------
    double x, w;
//--------------------------
    static const double d = 0.41893853320467274178032973640562;
//--------------------------
    if (a < 0.5) {
        return dgmln1(a) - log(a);
    } else if (a <= 2.5) {
         x = a - 1.0;
         if (a < 1.0) x = (a - 0.5) - 0.5;
         return dgmln1(x);
    } else if (a < 10.0) {
        int n = (int)(a - 1.5);
        x = a;
        w = 1.0;
        for (int i = 0; i < n; ++i) {
            x = x - 1.0;
            w = x*w;
        }
        return dgmln1(x - 1.0) + log(w);
    } else {
        w = __dj_dpdel(a);
        return (d + w) + (a - 0.5)*(log(a) - 1.0);
    }
}

static double
dgmln1(double x)
{
//-----------------------------------------------------------------------
//     EVALUATION OF LN(GAMMA(1 + X)) FOR -0.5 .LE. X .LE. 1.5
//-----------------------------------------------------------------------
    double w;
//-----------------------
    w = __dj_dgam1(x);
    /* Annex F requires +0 return for lgamma(1) and lgamma(2) */
    return w == 0.0 ? w : -log1p(w);
}
