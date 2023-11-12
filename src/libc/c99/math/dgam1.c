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
__dj_dgam1(double x)
{
//-----------------------------------------------------------------------
//     EVALUATION OF 1/GAMMA(1 + X) - 1  FOR -0.5 .LE. X .LE. 1.5
//-----------------------------------------------------------------------
//
//     THE FOLLOWING ARE THE FIRST 49 COEFFICIENTS OF THE MACLAURIN
//     EXPANSION FOR 1/GAMMA(1 + X) - 1. THE COEFFICIENTS ARE
//     CORRECT TO 40 DIGITS. THE COEFFICIENTS WERE OBTAINED BY
//     ALFRED H. MORRIS JR. (NAVAL SURFACE WARFARE CENTER) AND ARE
//     GIVEN HERE FOR REFERENCE. ONLY THE FIRST 14 COEFFICIENTS ARE
//     USED IN THIS CODE.
//
//                           -----------
//
//     DATA A(1)  / .5772156649015328606065120900824024310422D+00/,
//    *     A(2)  /-.6558780715202538810770195151453904812798D+00/,
//    *     A(3)  /-.4200263503409523552900393487542981871139D-01/,
//    *     A(4)  / .1665386113822914895017007951021052357178D+00/,
//    *     A(5)  /-.4219773455554433674820830128918739130165D-01/,
//    *     A(6)  /-.9621971527876973562114921672348198975363D-02/,
//    *     A(7)  / .7218943246663099542395010340446572709905D-02/,
//    *     A(8)  /-.1165167591859065112113971084018388666809D-02/,
//    *     A(9)  /-.2152416741149509728157299630536478064782D-03/,
//    *     A(10) / .1280502823881161861531986263281643233949D-03/
//     DATA A(11) /-.2013485478078823865568939142102181838229D-04/,
//    *     A(12) /-.1250493482142670657345359473833092242323D-05/,
//    *     A(13) / .1133027231981695882374129620330744943324D-05/,
//    *     A(14) /-.2056338416977607103450154130020572836513D-06/,
//    *     A(15) / .6116095104481415817862498682855342867276D-08/,
//    *     A(16) / .5002007644469222930055665048059991303045D-08/,
//    *     A(17) /-.1181274570487020144588126565436505577739D-08/,
//    *     A(18) / .1043426711691100510491540332312250191401D-09/,
//    *     A(19) / .7782263439905071254049937311360777226068D-11/,
//    *     A(20) /-.3696805618642205708187815878085766236571D-11/
//     DATA A(21) / .5100370287454475979015481322863231802727D-12/,
//    *     A(22) /-.2058326053566506783222429544855237419746D-13/,
//    *     A(23) /-.5348122539423017982370017318727939948990D-14/,
//    *     A(24) / .1226778628238260790158893846622422428165D-14/,
//    *     A(25) /-.1181259301697458769513764586842297831212D-15/,
//    *     A(26) / .1186692254751600332579777242928674071088D-17/,
//    *     A(27) / .1412380655318031781555803947566709037086D-17/,
//    *     A(28) /-.2298745684435370206592478580633699260285D-18/,
//    *     A(29) / .1714406321927337433383963370267257066813D-19/,
//    *     A(30) / .1337351730493693114864781395122268022875D-21/
//     DATA A(31) /-.2054233551766672789325025351355733796682D-21/,
//    *     A(32) / .2736030048607999844831509904330982014865D-22/,
//    *     A(33) /-.1732356445910516639057428451564779799070D-23/,
//    *     A(34) /-.2360619024499287287343450735427531007926D-25/,
//    *     A(35) / .1864982941717294430718413161878666898946D-25/,
//    *     A(36) /-.2218095624207197204399716913626860379732D-26/,
//    *     A(37) / .1297781974947993668824414486330594165619D-27/,
//    *     A(38) / .1180697474966528406222745415509971518560D-29/,
//    *     A(39) /-.1124584349277088090293654674261439512119D-29/,
//    *     A(40) / .1277085175140866203990206677751124647749D-30/
//     DATA A(41) /-.7391451169615140823461289330108552823711D-32/,
//    *     A(42) / .1134750257554215760954165259469306393009D-34/,
//    *     A(43) / .4639134641058722029944804907952228463058D-34/,
//    *     A(44) /-.5347336818439198875077418196709893320905D-35/,
//    *     A(45) / .3207995923613352622861237279082794391090D-36/,
//    *     A(46) /-.4445829736550756882101590352124643637401D-38/,
//    *     A(47) /-.1311174518881988712901058494389922190237D-38/,
//    *     A(48) / .1647033352543813886818259327906394145400D-39/,
//    *     A(49) /-.1056233178503581218600561071538285049997D-40/
//
//                           -----------
//
//     C = A(1) - 1 IS ALSO FREQUENTLY NEEDED. C HAS THE VALUE ...
//
//     DATA C /-.4227843350984671393934879099175975689578D+00/
//
//-----------------------------------------------------------------------
    double d, t, w, z;
//----------------------------
    static const double a0 =  .611609510448141581788E-08;
    static const double a1 =  .624730830116465516210E-08;
    static const double b1 =  .203610414066806987300E+00;
    static const double b2 =  .266205348428949217746E-01;
    static const double b3 =  .493944979382446875238E-03;
    static const double b4 = -.851419432440314906588E-05;
    static const double b5 = -.643045481779353022248E-05;
    static const double b6 =  .992641840672773722196E-06;
    static const double b7 = -.607761895722825260739E-07;
    static const double b8 =  .195755836614639731882E-09;
//----------------------------
    static const double p0 = .6116095104481415817861E-08;
    static const double p1 = .6871674113067198736152E-08;
    static const double p2 = .6820161668496170657918E-09;
    static const double p3 = .4686843322948848031080E-10;
    static const double p4 = .1572833027710446286995E-11;
    static const double p5 = .1249441572276366213222E-12;
    static const double p6 = .4343529937408594255178E-14;
    static const double q1 = .3056961078365221025009E+00;
    static const double q2 = .5464213086042296536016E-01;
    static const double q3 = .4956830093825887312020E-02;
    static const double q4 = .2692369466186361192876E-03;
//----------------------------
//     C = C0 - 1
//----------------------------
    static const double c = -.422784335098467139393487909917598E+00;
//----------------------------
    static const double c0  =  .577215664901532860606512090082402E+00;
    static const double c1  = -.655878071520253881077019515145390E+00;
    static const double c2  = -.420026350340952355290039348754298E-01;
    static const double c3  =  .166538611382291489501700795102105E+00;
    static const double c4  = -.421977345555443367482083012891874E-01;
    static const double c5  = -.962197152787697356211492167234820E-02;
    static const double c6  =  .721894324666309954239501034044657E-02;
    static const double c7  = -.116516759185906511211397108401839E-02;
    static const double c8  = -.215241674114950972815729963053648E-03;
    static const double c9  =  .128050282388116186153198626328164E-03;
    static const double c10 = -.201348547807882386556893914210218E-04;
    static const double c11 = -.125049348214267065734535947383309E-05;
    static const double c12 =  .113302723198169588237412962033074E-05;
    static const double c13 = -.205633841697760710345015413002057E-06;
//----------------------------
    t = x;
    d = x - 0.5;
    if (d > 0.0) t = d - 0.5;

    if (t == 0.0) {
        return 0.0;
    }
//------------
//
//                CASE WHEN 0 .LT. T .LE. 0.5
//
//              W IS A MINIMAX APPROXIMATION FOR
//              THE SERIES A(15) + A(16)*T + ...
//
//------------
    else if (t > 0.0) {
        w = ((((((p6*t + p5)*t + p4)*t + p3)*t + p2)*t + p1)*t + p0)/
              ((((q4*t + q3)*t + q2)*t + q1)*t + 1.0);
        z = (((((((((((((w*t + c13)*t + c12)*t + c11)*t + c10)*t +
                 c9)*t + c8)*t + c7)*t + c6)*t + c5)*t + c4)*t +
                 c3)*t + c2)*t + c1)*t + c0;

        if (d <= 0.0) {
            return x*z;
        } else {
            return (t/x)*((z - 0.5) - 0.5);
        }
//------------
//
//                CASE WHEN -0.5 .LE. T .LT. 0
//
//              W IS A MINIMAX APPROXIMATION FOR
//              THE SERIES A(15) + A(16)*T + ...
//
//------------
    } else {
        w = (a1*t + a0)/((((((((b8*t + b7)*t + b6)*t + b5)*t +
               b4)*t + b3)*t + b2)*t + b1)*t + 1.0);
        z = (((((((((((((w*t + c13)*t + c12)*t + c11)*t + c10)*t +
                 c9)*t + c8)*t + c7)*t + c6)*t + c5)*t + c4)*t +
                 c3)*t + c2)*t + c1)*t + c;

        if (d <= 0.0) {
            return x*((z + 0.5) + 0.5);
        } else {
            return t*z/x;
        }
    }
}

double
__dj_dpdel(double x)
{
//-----------------------------------------------------------------------
//
//     COMPUTATION OF THE FUNCTION DEL(X) FOR  X .GE. 10  WHERE
//     LN(GAMMA(X)) = (X - 0.5)*LN(X) - X + 0.5*LN(2*PI) + DEL(X)
//
//                         --------
//
//     THE SERIES FOR DPDEL ON THE INTERVAL 0.0 TO 1.0 DERIVED BY
//     A.H. MORRIS FROM THE CHEBYSHEV SERIES IN THE SLATEC LIBRARY
//     OBTAINED BY WAYNE FULLERTON (LOS ALAMOS).
//
//-----------------------------------------------------------------------
    double t, w;
//-----------------------------------------------------------------------
    static const double a[] = {
         .833333333333333333333333333333E-01,
        -.277777777777777777777777752282E-04,
         .793650793650793650791732130419E-07,
        -.595238095238095232389839236182E-09,
         .841750841750832853294451671990E-11,
        -.191752691751854612334149171243E-12,
         .641025640510325475730918472625E-14,
        -.295506514125338232839867823991E-15,
         .179643716359402238723287696452E-16,
        -.139228964661627791231203060395E-17,
         .133802855014020915603275339093E-18,
        -.154246009867966094273710216533E-19,
         .197701992980957427278370133333E-20,
        -.234065664793997056856992426667E-21,
         .171348014966398575409015466667E-22
    };
//-----------------------------------------------------------------------
    t = 100.0/(x*x);
    w = a[14];
    for (unsigned k = 14; k-- != 0; ) {
        w = t*w + a[k];
    }
    return w/x;
}

double
__dj_dsin1(double x)
{
    static const double pi = 3.14159265358979323846264338327950;
    return sin(pi * fmod(x, 2.0));
}