/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#ifndef __dj_include_complex_h_
#define __dj_include_complex_h_

#ifdef __cplusplus
extern "C" {
#endif

#define complex _Complex
#define _Complex_I __builtin_complex(0.0F, 1.0F)

#if 0
#define imaginary _Imaginary
#define _Imaginary_I __dj_Imaginary_I
extern const float _Imaginary __dj_Imaginary_I;
#endif

#ifdef _Imaginary_I
#define I _Imaginary_I
#else
#define I _Complex_I
#endif

#define CMPLX(x, y)  __builtin_complex((double)(x), (double)(y))
#define CMPLXF(x, y) __builtin_complex((float)(x), (float)(y))
#define CMPLXL(x, y) __builtin_complex((long double)(x), (long double)(y))

extern double complex cacos(double complex /*z*/);
extern float complex cacosf(float complex /*z*/);
extern long double complex cacosl(long double complex /*z*/);
extern double complex casin(double complex /*z*/);
extern float complex casinf(float complex /*z*/);
extern long double complex casinl(long double complex /*z*/);
extern double complex catan(double complex /*z*/);
extern float complex catanf(float complex /*z*/);
extern long double complex catanl(long double complex /*z*/);
extern double complex ccos(double complex /*z*/);
extern float complex ccosf(float complex /*z*/);
extern long double complex ccosl(long double complex /*z*/);
extern double complex csin(double complex /*z*/);
extern float complex csinf(float complex /*z*/);
extern long double complex csinl(long double complex /*z*/);
extern double complex ctan(double complex /*z*/);
extern float complex ctanf(float complex /*z*/);
extern long double complex ctanl(long double complex /*z*/);
extern double complex cacosh(double complex /*z*/);
extern float complex cacoshf(float complex /*z*/);
extern long double complex cacoshl(long double complex /*z*/);
extern double complex casinh(double complex /*z*/);
extern float complex casinhf(float complex /*z*/);
extern long double complex casinhl(long double complex /*z*/);
extern double complex catanh(double complex /*z*/);
extern float complex catanhf(float complex /*z*/);
extern long double complex catanhl(long double complex /*z*/);
extern double complex ccosh(double complex /*z*/);
extern float complex ccoshf(float complex /*z*/);
extern long double complex ccoshl(long double complex /*z*/);
extern double complex csinh(double complex /*z*/);
extern float complex csinhf(float complex /*z*/);
extern long double complex csinhl(long double complex /*z*/);
extern double complex ctanh(double complex /*z*/);
extern float complex ctanhf(float complex /*z*/);
extern long double complex ctanhl(long double complex /*z*/);
extern double complex cexp(double complex /*z*/);
extern float complex cexpf(float complex /*z*/);
extern long double complex cexpl(long double complex /*z*/);
extern double complex clog(double complex /*z*/);
extern float complex clogf(float complex /*z*/);
extern long double complex clogl(long double complex /*z*/);
extern double cabs(double complex /*z*/);
extern float cabsf(float complex /*z*/);
extern long double cabsl(long double complex /*z*/);
extern double complex cpow(double complex /*x*/, double complex /*y*/);
extern float complex cpowf(float complex /*x*/, float complex /*y*/);
extern long double complex cpowl(long double complex /*x*/,
        long double complex /*y*/);
extern double complex csqrt(double complex /*z*/);
extern float complex csqrtf(float complex /*z*/);
extern long double complex csqrtl(long double complex /*z*/);
extern double carg(double complex /*z*/);
extern float cargf(float complex /*z*/);
extern long double cargl(long double complex /*z*/);
extern double cimag(double complex /*z*/);
extern float cimagf(float complex /*z*/);
extern long double cimagl(long double complex /*z*/);
extern double complex conj(double complex /*z*/);
extern float complex conjf(float complex /*z*/);
extern long double complex conjl(long double complex /*z*/);
extern double complex cproj(double complex /*z*/);
extern float complex cprojf(float complex /*z*/);
extern long double complex cprojl(long double complex /*z*/);
extern double creal(double complex /*z*/);
extern float crealf(float complex /*z*/);
extern long double creall(long double complex /*z*/);

#ifdef __cplusplus
};
#endif

#endif /* __dj_include_complex_h_ */
