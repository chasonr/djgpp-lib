/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

/*
 * Private header for functions common to fma and fmal
 *
 * __dj_big_fma implements the fma function using double-double algorithms.
 * The return type is an array of three long doubles, which can exactly
 * represent any finite result from the fma function.
 *
 * 32-bit x86 does all floating point arithmetic in 80 bit long double.
 * Double-double algorithms depend on the arithmetic rounding exactly as the
 * IEEE standard says. For this reason, the double-double algorithms are
 * adapted to the long double type.
 *
 * fmaf uses a simpler algorithm, with double-double only for addition,
 * because one long double can represent the result of any multiplication
 * of floats.
 */

#ifndef BIG_FMA_H
#define BIG_FMA_H

extern void __dj_big_fma(
        long double x, long double y, long double z,
        long double sum[3]);
extern long double __dj_two_sum(long double a, long double b, long double *err);
extern long double __dj_set_odd(long double a);

#endif
