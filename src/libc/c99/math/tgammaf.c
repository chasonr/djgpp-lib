/*
 * Converted from nswclibr.f, a public domain work of the United States
 * Government, available at https://dev.aao.org.au/rds/nswc among other
 * places.
 * Conversion by Ray Chason, 2023.
 * Comments are as in the original code. Changes are made for Annex F
 * conformance.
 */

#include <errno.h>
#include <math.h>

float
tgammaf(float a)
{
//-----------------------------------------------------------------------
//
//         EVALUATION OF THE GAMMA FUNCTION FOR REAL ARGUMENTS
//
//                           -----------
//
//     GAMMA(A) IS ASSIGNED THE VALUE 0 WHEN THE GAMMA FUNCTION CANNOT
//     BE COMPUTED.
//     RLC: Error value is NaN or infinity according to Annex F
//
//-----------------------------------------------------------------------
//     WRITTEN BY ALFRED H. MORRIS, JR.
//          NAVAL SURFACE WEAPONS CENTER
//          DAHLGREN, VIRGINIA
//-----------------------------------------------------------------------
    double g, z, lnx;
    float s = 0.0F, top, bot, x, t, w;
    int n;
//--------------------------
//     D = 0.5*(LN(2*PI) - 1)
//--------------------------
    static const float pi = 3.1415926535898F;
    static const double d = .41893853320467274178;
//--------------------------
    static const float p[] = {
        .539637273585445E-03F,  .261939260042690E-02F,
        .204493667594920E-01F,  .730981088720487E-01F,
        .279648642639792E+00F,  .553413866010467E+00F,
        1.0F
    };
    static const float q[] = {
        -.832979206704073E-03F,   .470059485860584E-02F,
         .225211131035340E-01F,  -.170458969313360E+00F,
        -.567902761974940E-01F,   .113062953091122E+01F,
         1.0F
    };
//--------------------------
    static const float
           r1 = .820756370353826E-03F, r2 = -.595156336428591E-03F,
           r3 = .793650663183693E-03F, r4 = -.277777777770481E-02F,
           r5 = .833333333333333E-01F;
//--------------------------
    float rval = 0.0F;
    x = a;
    if (fabsf(a) < 15.0F) {
//-----------------------------------------------------------------------
//            EVALUATION OF GAMMA(A) FOR ABS(A) .LT. 15
//-----------------------------------------------------------------------
        t = 1.0F;
        int m = (int)a - 1;
//
//     LET T BE THE PRODUCT OF A-J WHEN A .GE. 2
//
        if (m >= 0) {
            for (int j = 0; j < m; ++j) {
                x = x - 1.0F;
                t = x*t;
            }
            x = x - 1.0F;
        }
//
//     LET T BE THE PRODUCT OF A+J WHEN A .LT. 1
//
        else {
            t = a;
            if (a <= 0.0F) {
                m = - m - 1;
                for (int j = 0; j < m; ++j) {
                    x = x + 1.0F;
                    t = x*t;
                }
                x = (x + 0.5F) + 0.5F;
                t = x*t;
                if (t == 0.0F) {
                    if (a == 0.0F) {
                        errno = ERANGE;
                        return 1.0F/a;
                    } else {
                        errno = EDOM;
                        return 0.0F/0.0F;
                    }
                }
            }
        }
//
//     COMPUTE GAMMA(1 + X) FOR  0 .LE. X .LT. 1
//
        top = p[0];
        bot = q[0];
        for (unsigned i = 1; i < 7; ++i) {
            top = p[i] + x*top;
            bot = q[i] + x*bot;
        }
        rval = top/bot;
//
//     TERMINATION
//
        if (a >= 1.0F) {
            rval *= t;
        } else {
            rval /= t;
        }
    }
//-----------------------------------------------------------------------
//            EVALUATION OF GAMMA(A) FOR ABS(A) .GE. 15
//-----------------------------------------------------------------------
    else {
        if (a <= 0.0F) {
            x = -a;
            n = x;
            t = x - n;
            if (t > 0.9F) t = 1.0F - t;
            s = sinf(pi*t)/pi;
            if (n % 2 == 0) s = -s;
            if (s == 0.0F) {
                errno = EDOM;
                return 0.0F/0.0F;
            }
        }
//
//     COMPUTE THE MODIFIED ASYMPTOTIC SUM
//
        t = 1.0F/(x*x);
        g = ((((r1*t + r2)*t + r3)*t + r4)*t + r5)/x;
//
//     ONE MAY REPLACE THE NEXT STATEMENT WITH  LNX = ALOG(X)
//     BUT LESS ACCURACY WILL NORMALLY BE OBTAINED.
//     RLC: for C, this means logf(x)
//
        lnx = log(x);
//
//     FINAL ASSEMBLY
//
        z = x;
        g = (d + g) + (z - 0.5)*(lnx - 1.0);
        w = g;
        t = g - (double)w;
        if (a >= 0.0F) {
            rval = expf(w)*(1.0F + t);
        } else {
            /* Use double precision here to get subnormal results right */
            double drval = exp(w)*(1.0F + t);
            rval = (float)((1.0/(drval*(double)s))/(double)x);
        }
    }
    if (isinf(rval)) {
        errno = ERANGE;
    }
    return rval;
}
