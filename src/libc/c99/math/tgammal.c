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

long double
tgammal(long double a)
{
//-----------------------------------------------------------------------
//
//                EVALUATION OF THE GAMMA FUNCTION FOR
//                     DOUBLE PRECISION ARGUMENTS
//
//                           -----------
//
//     DGAMMA(A) IS ASSIGNED THE VALUE NaN WHEN THE GAMMA FUNCTION CANNOT
//     BE COMPUTED.
//
//-----------------------------------------------------------------------
//     WRITTEN BY ALFRED H. MORRIS, JR.
//          NAVAL SURFACE WEAPONS CENTER
//          DAHLGREN, VIRGINIA
//-----------------------------------------------------------------------
    long double s, t, x, w;
//-----------------------------------------------------------------------
//     D = 0.5*(LN(2*PI) - 1)
//-----------------------------------------------------------------------
    static const long double pi = 3.14159265358979323846264338327950L;
    static const long double d  = 0.41893853320467274178032973640562L;
//-----------------------------------------------------------------------
    long double rval = 0.0L;
    if (isnan(a)) {
        return a;
    }
    x = a;
    if (fabsl(a) <= 20.0L) {
//-----------------------------------------------------------------------
//             EVALUATION OF DGAMMA(A) FOR DABS(A) .LE. 20
//-----------------------------------------------------------------------
        t = 1.0L;
        int n = x;
        n = n - 1;
//
//     LET T BE THE PRODUCT OF A-J WHEN A .GE. 2
//
        if (n >= 0) {
            if (n != 0) {
                for (int j = 0; j < n; ++j) {
                    x = x - 1.0L;
                    t = x*t;
                }
            }
            x = x - 1.0L;
        }
//
//     LET T BE THE PRODUCT OF A+J WHEN A .LT. 1
//
        else {
            t = a;
            if (a <= 0.0L) {
                n = - n - 1;
                if (n != 0) {
                    for (int j = 0; j < n; ++j) {
                        x = x + 1.0L;
                        t = x*t;
                    }
                }
                x = (x + 0.5L) + 0.5L;
                t = x*t;
                if (t == 0.0L) {
                    /* Return and raise exceptions according to Annex F */
                    if (a == 0.0L) {
                        return +1.0L/a; /* infinity with correct sign */
                    } else {
                        return 0.0L/0.0L; /* NaN */
                    }
                }
            }
        }
//
//     COMPUTE DGAMMA(1 + X) FOR 0 .LE. X .LT. 1
//
        rval = 1.0L/(1.0L + __dj_dgam1l(x));
//
//     TERMINATION
//
        if (a >= 1.0L) {
            rval = rval * t;
            return rval;
        }
        rval = rval / t;
        return rval;
    }
//-----------------------------------------------------------------------
//           EVALUATION OF DGAMMA(A) FOR DABS(A) .GT. 20
//-----------------------------------------------------------------------
    else {
        if (a <= 0.0L) {
            s = __dj_dsin1l(a)/pi;
            if (s == 0.0L) return 0.0L/0.0L;
            x = -a;
        }
//
//     COMPUTE THE MODIFIED ASYMPTOTIC SUM
//
        w = __dj_dpdell(x);
//
//     FINAL ASSEMBLY
//
        w = (d + w) + (x - 0.5L)*(logl(x) - 1.0L);
        if (a < 0.0L) {
            rval = expl(-(w + logl(x*fabsl(s))));
            if (s < 0.0L) {
                rval = -rval;
            }
        } else {
            rval = expl(w);
        }
        return rval;
    }
}
