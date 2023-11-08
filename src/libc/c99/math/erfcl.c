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
#include "derfc0.h"

long double
erfcl(long double x)
{
//-----------------------------------------------------------------------
//         EVALUATION OF THE COMPLEMENTARY ERROR FUNCTION
//-----------------------------------------------------------------------
    long double ax, t, w;
//-------------------------------
    static const long double a[] = {
         .1283791670955125738961589031215E+00L,
        -.3761263890318375246320529677070E+00L,
         .1128379167095512573896158902931E+00L,
        -.2686617064513125175943235372542E-01L,
         .5223977625442187842111812447877E-02L,
        -.8548327023450852832540164081187E-03L,
         .1205533298178966425020717182498E-03L,
        -.1492565035840625090430728526820E-04L,
         .1646211436588924261080723578109E-05L,
        -.1636584469123468757408968429674E-06L,
         .1480719281587021715400818627811E-07L,
        -.1229055530145120140800510155331E-08L,
         .9422759058437197017313055084212E-10L,
        -.6711366740969385085896257227159E-11L,
         .4463222608295664017461758843550E-12L,
        -.2783497395542995487275065856998E-13L,
         .1634095572365337143933023780777E-14L,
        -.9052845786901123985710019387938E-16L,
         .4708274559689744439341671426731E-17L,
        -.2187159356685015949749948252160E-18L,
         .7043407712019701609635599701333E-20L
    };
//-------------------------------
    if (isnan(x)) {
        return x;
    }
//
//                     DABS(X) .LE. 1
//
    ax = fabsl(x);
    if (ax <= 1.0L) {
        t = x*x;
        w = a[20];
        for (unsigned k = 20; k-- != 0; ) {
            w = t*w + a[k];
        }
        return 0.5L + (0.5L - x*(1.0 + w));
    }
//
//                       X .LT. -1
//
    else if (x <= 0.0L) {
        if (x < -8.3L) {
            return 2.0L;
        }
        t = x*x;
        return 2.0L - expl(-t) * __dj_derfc0l(ax);
    }
//
//                       X .GT. 1
//
    else {
        if (x > +107.0L) {
            return 0.0L;
        }
        t = x*x;
        return expl(-t) * __dj_derfc0l(x);
    }
}
