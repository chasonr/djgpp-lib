/* Common elements between tgamma{f,,l} and lgamma{f,,l} */

#ifndef DGAM1_H
#define DGAM1_H

extern double __dj_dgam1(double x);
extern double __dj_dpdel(double x);
extern double __dj_dsin1(double x);
extern long double __dj_dgam1l(long double x);
extern long double __dj_dpdell(long double x);
extern long double __dj_dsin1l(long double x);

#endif
