/*
 * Converted from nswclibr.f, a public domain work of the United States
 * Government, available at https://dev.aao.org.au/rds/nswc among other
 * places.
 * Conversion by Ray Chason, 2023.
 * The original uses the DOUBLE PRECISION type, but the algorithms are
 * adequate for long double.
 * Comments are as in the original code. Changes are made to support the
 * long double type and for Annex F conformance.
 */

#include <math.h>
#include "dgam1.h"

static long double dgamln(long double x);
static long double dgmln1(long double x);

long double
lgammal(long double a)
{
    static const long double pi = 3.14159265358979323846264338327950L;

    if (isnan(a)) {
        return a;
    } else if (a >= 0.0L) {
        return dgamln(a);
    } else {
        if (isinf(a)) {
            return HUGE_VAL;
        } else if (fmodl(a, 1.0L) == 0.0L) {
            return 1.0L/0.0L;
        } else {
            long double prod = pi/__dj_dsin1l(a);
            return logl(fabsl(prod)) - dgamln(1.0L - a);
        }
    }
}

static long double
dgamln(long double a)
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
    long double x, w;
//--------------------------
    static const long double d = 0.41893853320467274178032973640562L;
//--------------------------
    if (a < 0.5L) {
        return dgmln1(a) - logl(a);
    } else if (a <= 2.5L) {
         x = a - 1.0L;
         if (a < 1.0L) x = (a - 0.5L) - 0.5L;
         return dgmln1(x);
    } else if (a < 10.0L) {
        int n = (int)(a - 1.5L);
        x = a;
        w = 1.0L;
        for (int i = 0; i < n; ++i) {
            x = x - 1.0L;
            w = x*w;
        }
        return dgmln1(x - 1.0L) + logl(w);
    } else {
        w = __dj_dpdell(a);
        return (d + w) + (a - 0.5L)*(logl(a) - 1.0L);
    }
}

static long double
dgmln1(long double x)
{
//-----------------------------------------------------------------------
//     EVALUATION OF LN(GAMMA(1 + X)) FOR -0.5 .LE. X .LE. 1.5
//-----------------------------------------------------------------------
    long double w;
//-----------------------
    w = __dj_dgam1l(x);
    /* Annex F requires +0 return for lgamma(1) and lgamma(2) */
    return w == 0.0L ? w : -log1pl(w);
}
