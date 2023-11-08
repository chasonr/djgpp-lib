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

static float gamln(float a);
static float gamln1(float a);

float
lgammaf(float a)
{
    static const float pi = 3.14159265358979323846264338327950F;

    if (isnan(a)) {
        return a;
    } else if (a >= 0.0F) {
        return gamln(a);
    } else {
        if (isinf(a)) {
            return HUGE_VAL;
        } else if (fmodf(a, 1.0F) == 0.0F) {
            errno = EDOM;
            return 1.0F/0.0F;
        } else {
            double prod = pi/sinf(pi*fmodf(a, 2.0F));
            return logf(fabsf(prod)) - gamln(1.0F - a);
        }
    }
}

static float
gamln(float a)
{
//-----------------------------------------------------------------------
//            EVALUATION OF LN(GAMMA(A)) FOR POSITIVE A
//-----------------------------------------------------------------------
//     WRITTEN BY ALFRED H. MORRIS
//          NAVAL SURFACE WARFARE CENTER
//          DAHLGREN, VIRGINIA
//--------------------------
//     D = 0.5*(LN(2*PI) - 1)
//--------------------------
    static const float d = .418938533204673F;
//--------------------------
    static const float
           c0 = .833333333333333E-01F, c1 = -.277777777760991E-02F,
           c2 = .793650666825390E-03F, c3 = -.595202931351870E-03F,
           c4 = .837308034031215E-03F, c5 = -.165322962780713E-02F;
//-----------------------------------------------------------------------
    float t, w;
    int n;
    if (a <= 0.8F) {
        return gamln1(a) - logf(a);
    } else if (a <= 2.25F) {
        t = (a - 0.5) - 0.5;
        return gamln1(t);
    } else if (a < 10.0F) {
        n = a - 1.25F;
        t = a;
        w = 1.0F;
        for (int i = 0; i < n; ++i) {
            t = t - 1.0F;
            w = t*w;
        }
        return gamln1(t - 1.0F) + logf(w);
    } else {
        t = 1.0F/(a*a);
        w = (((((c5*t + c4)*t + c3)*t + c2)*t + c1)*t + c0)/a;
        return (d + w) + (a - 0.5F)*(logf(a) - 1.0F);
    }
}

static float
gamln1(float a)
{
//-----------------------------------------------------------------------
//     EVALUATION OF LN(GAMMA(1 + A)) FOR -0.2 .LE. A .LE. 1.25
//-----------------------------------------------------------------------
    static const float
           p0 =  .577215664901533E+00F, p1 =  .844203922187225E+00F,
           p2 = -.168860593646662E+00F, p3 = -.780427615533591E+00F,
           p4 = -.402055799310489E+00F, p5 = -.673562214325671E-01F,
           p6 = -.271935708322958E-02F;
    static const float
           q1 =  .288743195473681E+01F, q2 =  .312755088914843E+01F,
           q3 =  .156875193295039E+01F, q4 =  .361951990101499E+00F,
           q5 =  .325038868253937E-01F, q6 =  .667465618796164E-03F;
//----------------------
    static const float
           r0 = .422784335098467E+00F,  r1 = .848044614534529E+00F,
           r2 = .565221050691933E+00F,  r3 = .156513060486551E+00F,
           r4 = .170502484022650E-01F,  r5 = .497958207639485E-03F;
    static const float
           s1 = .124313399877507E+01F,  s2 = .548042109832463E+00F,
           s3 = .101552187439830E+00F,  s4 = .713309612391000E-02F,
           s5 = .116165475989616E-03F;
//----------------------
    float w, x;
    if (a <= 0.6F) {
        w = ((((((p6*a + p5)*a + p4)*a + p3)*a + p2)*a + p1)*a + p0)/
            ((((((q6*a + q5)*a + q4)*a + q3)*a + q2)*a + q1)*a + 1.0F);
        return -a*w;
    } else {
        x = (a - 0.5F) - 0.5F;
        w = (((((r5*x + r4)*x + r3)*x + r2)*x + r1)*x + r0)/
            (((((s5*x + s4)*x + s3)*x + s2)*x + s1)*x + 1.0F);
        return x*w;
    }
}
