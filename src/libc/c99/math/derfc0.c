/*
 * Converted from nswclibr.f, a public domain work of the United States
 * Government, available at https://dev.aao.org.au/rds/nswc among other
 * places.
 * Conversion by Ray Chason, 2023.
 * Comments are as in the original code. Changes are made for Annex F
 * conformance.
 */

#include <math.h>
#include "derfc0.h"

double
__dj_derfc0(double x)
{
//-----------------------------------------------------------------------
//
//           EVALUATION OF EXP(X**2)*ERFC(X) FOR X .GE. 1
//
//-----------------------------------------------------------------------
//     WRITTEN BY ALFRED H. MORRIS, JR.
//        NAVAL SURFACE WARFARE CENTER
//        DAHLGREN, VIRGINIA
//        APRIL 1992
//-------------------------------
    double t, u, v, z;
//-------------------------------
//     RPINV = 1/SQRT(PI)
//-------------------------------
    static const double rpinv = .56418958354775628694807945156077259E0;
//-------------------------------
    static const double p0 =  .16506148041280876191828601E-03;
    static const double p1 =  .15471455377139313353998665E-03;
    static const double p2 =  .44852548090298868465196794E-04;
    static const double p3 = -.49177280017226285450486205E-05;
    static const double p4 = -.69353602078656412367801676E-05;
    static const double p5 = -.20508667787746282746857743E-05;
    static const double p6 = -.28982842617824971177267380E-06;
    static const double p7 = -.17272433544836633301127174E-07;
    static const double q1 =  .16272656776533322859856317E+01;
    static const double q2 =  .12040996037066026106794322E+01;
    static const double q3 =  .52400246352158386907601472E+00;
    static const double q4 =  .14497345252798672362384241E+00;
    static const double q5 =  .25592517111042546492590736E-01;
    static const double q6 =  .26869088293991371028123158E-02;
    static const double q7 =  .13133767840925681614496481E-03;
//-------------------------------
    static const double r0 =  .145589721275038539045668824025E+00;
    static const double r1 = -.273421931495426482902320421863E+00;
    static const double r2 =  .226008066916621506788789064272E+00;
    static const double r3 = -.163571895523923805648814425592E+00;
    static const double r4 =  .102604312032193978662297299832E+00;
    static const double r5 = -.548023266949835519254211506880E-01;
    static const double r6 =  .241432239725390106956523668160E-01;
    static const double r7 = -.822062115403915116036874169600E-02;
    static const double r8 =  .180296241564687154310619200000E-02;
//-------------------------------
    static const double a0 = -.45894433406309678202825375E-03;
    static const double a1 = -.12281298722544724287816236E-01;
    static const double a2 = -.91144359512342900801764781E-01;
    static const double a3 = -.28412489223839285652511367E-01;
    static const double a4 =  .14083827189977123530129812E+01;
    static const double a5 =  .11532175281537044570477189E+01;
    static const double a6 = -.72170903389442152112483632E+01;
    static const double a7 = -.19685597805218214001309225E+01;
    static const double a8 =  .93846891504541841150916038E+01;
    static const double b1 =  .25136329960926527692263725E+02;
    static const double b2 =  .15349442087145759184067981E+03;
    static const double b3 = -.29971215958498680905476402E+03;
    static const double b4 = -.33876477506888115226730368E+04;
    static const double b5 =  .28301829314924804988873701E+04;
    static const double b6 =  .22979620942196507068034887E+05;
    static const double b7 = -.24280681522998071562462041E+05;
    static const double b8 = -.36680620673264731899504580E+05;
    static const double b9 =  .42278731622295627627042436E+05;
    static const double b10=  .28834257644413614344549790E+03;
    static const double b11=  .70226293775648358646587341E+03;
//-------------------------------
    static const double c0 = -.7040906288250128001000086E-04;
    static const double c1 = -.3858822461760510359506941E-02;
    static const double c2 = -.7708202127512212359395078E-01;
    static const double c3 = -.6713655014557429480440263E+00;
    static const double c4 = -.2081992124162995545731882E+01;
    static const double c5 =  .2898831421475282558867888E+01;
    static const double c6 =  .2199509380600429331650192E+02;
    static const double c7 =  .2907064664404115316722996E+01;
    static const double c8 = -.4766208741588182425380950E+02;
    static const double d1 =  .5238852785508439144747174E+02;
    static const double d2 =  .9646843357714742409535148E+03;
    static const double d3 =  .7007152775135939601804416E+04;
    static const double d4 =  .8515386792259821780601162E+04;
    static const double d5 = -.1002360095177164564992134E+06;
    static const double d6 = -.2065250031331232815791912E+06;
    static const double d7 =  .5695324805290370358175984E+06;
    static const double d8 =  .6589752493461331195697873E+06;
    static const double d9 = -.1192930193156561957631462E+07;
//-------------------------------
    static const double e0 =  .540464821348814822409610122136E+00;
    static const double e1 = -.261515522487415653487049835220E-01;
    static const double e2 = -.288573438386338758794591212600E-02;
    static const double e3 = -.529353396945788057720258856000E-03;
//-------------------------------
//     COEFFICIENTS FOR THE ASYMPTOTIC EXPANSION
//-------------------------------
    static const double s1  =  .75000000000000000000E+00;
    static const double s2  = -.18750000000000000000E+01;
    static const double s3  =  .65625000000000000000E+01;
    static const double s4  = -.29531250000000000000E+02;
    static const double s5  =  .16242187500000000000E+03;
    static const double s6  = -.10557421875000000000E+04;
    static const double s7  =  .79180664062500000000E+04;
    static const double s8  = -.67303564453125000000E+05;
    static const double s9  =  .63938386230468750000E+06;
    static const double s10 = -.67135305541992187500E+07;
    static const double s11 =  .77205601373291015625E+08;
//-------------------------------
//
//                     1 .LE. X .LE. 2
//
    if (x <= 2.0) {
        u = ((((((p7*x + p6)*x + p5)*x + p4)*x + p3)*x +
                  p2)*x + p1)*x + p0;
        v = ((((((q7*x + q6)*x + q5)*x + q4)*x + q3)*x +
                  q2)*x + q1)*x + 1.0;

        t = (x - 3.75)/(x + 3.75);
        return (((((((((u/v)*t + r8)*t + r7)*t + r6)*t + r5)*t +
                         r4)*t + r3)*t + r2)*t + r1)*t + r0;
    }
//
//                     2 .LT. X .LE. 4
//
    else if (x <= 4.0) {
        z = 1.0/(2.5 + x*x);
        u = (((((((a8*z + a7)*z + a6)*z + a5)*z + a4)*z + a3)*z +
                          a2)*z + a1)*z + a0;
        v = ((((((((((b11*z + b10)*z + b9)*z + b8)*z + b7)*z + b6)*z +
                      b5)*z + b4)*z + b3)*z + b2)*z + b1)*z + 1.0;

        t = 13.0*z - 1.0;
        return ((((u/v)*t + e2)*t + e1)*t + e0)/x;
    }
//
//                     4 .LT. X .LT. 50
//
    else if (x < 50.0) {
        z = 1.0/(2.5 + x*x);
        u = (((((((c8*z + c7)*z + c6)*z + c5)*z + c4)*z + c3)*z +
                          c2)*z + c1)*z + c0;
        v = ((((((((d9*z + d8)*z + d7)*z + d6)*z + d5)*z + d4)*z +
                           d3)*z + d2)*z + d1)*z + 1.0;

        t = 13.0*z - 1.0;
        return (((((u/v)*t + e3)*t + e2)*t + e1)*t + e0)/x;
    }
//
//                        X .GE. 50
//
    else {
        t = 1.0/(x*x);
        z = (((((((((((s11*t + s10)*t + s9)*t + s8)*t + s7)*t +
                s6)*t + s5)*t + s4)*t + s3)*t + s2)*t + s1)*t -
                0.5)*t + 1.0;
        return rpinv*(z/x);
    }
}
