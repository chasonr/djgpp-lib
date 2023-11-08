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
erff(float x)
{
//-----------------------------------------------------------------------
//             EVALUATION OF THE REAL ERROR FUNCTION
//-----------------------------------------------------------------------
//-------------------------
    static const float c = .564189583547756F;
//-------------------------
    static const float a[] = {
         .771058495001320E-04F, -.133733772997339E-02F,
         .323076579225834E-01F,  .479137145607681E-01F,
         .128379167095513E+00F
    };
    static const float b[] = {
         .301048631703895E-02F,  .538971687740286E-01F,
         .375795757275549E+00F
    };
//-------------------------
    static const float p[] = {
        -1.36864857382717E-07F,  5.64195517478974E-01F,
         7.21175825088309E+00F,  4.31622272220567E+01F,
         1.52989285046940E+02F,  3.39320816734344E+02F,
         4.51918953711873E+02F,  3.00459261020162E+02F
    };
    static const float q[] = {
         1.00000000000000E+00F,  1.27827273196294E+01F,
         7.70001529352295E+01F,  2.77585444743988E+02F,
         6.38980264465631E+02F,  9.31354094850610E+02F,
         7.90950925327898E+02F,  3.00459260956983E+02F
    };
//-------------------------
    static const float r[] = {
         2.10144126479064E+00F,  2.62370141675169E+01F,
         2.13688200555087E+01F,  4.65807828718470E+00F,
         2.82094791773523E-01F
    };
    static const float s[] = {
         9.41537750555460E+01F,  1.87114811799590E+02F,
         9.90191814623914E+01F,  1.80124575948747E+01F
    };
//-------------------------
    float ax, t, top, bot, x2, erf;

    ax = fabsf(x);
    if (ax <= 0.5F) {
        t = x*x;
        top = ((((a[0]*t + a[1])*t + a[2])*t + a[3])*t + a[4]) + 1.0F;
        bot = ((b[0]*t + b[1])*t + b[2])*t + 1.0F;
        erf = x*(top/bot);
    } else if (ax <= 4.0F) {
        top = ((((((p[0]*ax + p[1])*ax + p[2])*ax + p[3])*ax + p[4])*ax
                            + p[5])*ax + p[6])*ax + p[7];
        bot = ((((((q[0]*ax + q[1])*ax + q[2])*ax + q[3])*ax + q[4])*ax
                            + q[5])*ax + q[6])*ax + q[7];
        erf = 0.5F + (0.5F - expf(-x*x)*top/bot);
    } else if (ax < 5.8F) {
        x2 = x*x;
        t = 1.0F/x2;
        top = (((r[0]*t + r[1])*t + r[2])*t + r[3])*t + r[4];
        bot = (((s[0]*t + s[1])*t + s[2])*t + s[3])*t + 1.0F;
        erf = (c - top/(x2*bot)) / ax;
        erf = 0.5F + (0.5F - expf(-x2)*erf);
    } else {
        erf = 1.0F;
    }
    return copysignf(erf, x);
}
