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

double
tgamma(double a)
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
    double s = 0.0, t, x, w;
//-----------------------------------------------------------------------
//     D = 0.5*(LN(2*PI) - 1)
//-----------------------------------------------------------------------
    static const double pi = 3.14159265358979323846264338327950;
    static const double d  = 0.41893853320467274178032973640562;
//-----------------------------------------------------------------------
    double rval = 0.0;
    if (isnan(a)) {
        return a;
    }
    x = a;
    if (fabs(a) <= 20.0) {
//-----------------------------------------------------------------------
//             EVALUATION OF DGAMMA(A) FOR DABS(A) .LE. 20
//-----------------------------------------------------------------------
        t = 1.0;
        int n = x;
        n = n - 1;
//
//     LET T BE THE PRODUCT OF A-J WHEN A .GE. 2
//
        if (n >= 0) {
            if (n != 0) {
                for (int j = 0; j < n; ++j) {
                    x = x - 1.0;
                    t = x*t;
                }
            }
            x = x - 1.0;
        }
//
//     LET T BE THE PRODUCT OF A+J WHEN A .LT. 1
//
        else {
            t = a;
            if (a <= 0.0) {
                n = - n - 1;
                if (n != 0) {
                    for (int j = 0; j < n; ++j) {
                        x = x + 1.0;
                        t = x*t;
                    }
                }
                x = (x + 0.5) + 0.5;
                t = x*t;
                if (t == 0.0) {
                    /* Return and raise exceptions according to Annex F */
                    if (a == 0.0) {
                        return +1.0/a; /* infinity with correct sign */
                    } else {
                        return 0.0/0.0; /* NaN */
                    }
                }
            }
        }
//
//     COMPUTE DGAMMA(1 + X) FOR 0 .LE. X .LT. 1
//
        rval = 1.0/(1.0 + __dj_dgam1(x));
//
//     TERMINATION
//
        if (a >= 1.0) {
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
        if (a <= 0.0) {
            s = __dj_dsin1(a)/pi;
            if (s == 0.0) return 0.0/0.0;
            x = -a;
        }
//
//     COMPUTE THE MODIFIED ASYMPTOTIC SUM
//
        w = __dj_dpdel(x);
//
//     FINAL ASSEMBLY
//
        w = (d + w) + (x - 0.5)*(log(x) - 1.0);
        if (a < 0.0) {
            rval = exp(-(w + log(x*fabs(s))));
            if (s < 0.0) {
                rval = -rval;
            }
        } else {
            rval = exp(w);
        }
        return rval;
    }
}
