/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

#ifndef __dj_include_fenv_h_
#define __dj_include_fenv_h_

#ifdef __cplusplus
extern "C" {
#endif

/* The features enumerated in ieeefp.h are not in fact implemented.
   Definitions are according to the x86 architecture. */

/* Rounding direction */
/* Bits according to the x86 floating point control register */
#define FE_TONEAREST  0
#define FE_DOWNWARD   1
#define FE_UPWARD     2
#define FE_TOWARDZERO 3

typedef struct __dj_fenv_t {
    unsigned __x87control;
    unsigned __x87flags;
    unsigned __ssecontrol;
} fenv_t;

typedef struct __dj_fexcept_t {
    unsigned __x87flags;
    unsigned __sseflags;
} fexcept_t;

/* Bits according to the x86 floating point status register */
#define FE_INEXACT   0x20
#define FE_UNDERFLOW 0x10
#define FE_OVERFLOW  0x08
#define FE_DIVBYZERO 0x04
#define FE_SUBNORMAL 0x02
#define FE_DENORMAL  FE_SUBNORMAL
#define FE_INVALID   0x01

#define FE_ALL_EXCEPT 0x3F

extern const fenv_t __dj_fe_dfl_env;
#define FE_DFL_ENV (&__dj_fe_dfl_env)

int feclearexcept(int _excepts);
int fegetexceptflag(fexcept_t *_flagp, int _excepts);
int feraiseexcept(int _excepts);
int fesetexceptflag(const fexcept_t *_flagp, int _excepts);
int fetestexcept(int _excepts);
int fegetround(void);
int fesetround(int _round);
int fegetenv(fenv_t *_envp);
int feholdexcept(fenv_t *_envp);
int fesetenv(const fenv_t *_envp);
int feupdateenv(const fenv_t *_envp);

#ifdef __cplusplus
}
#endif

#endif /* __dj_include_fenv_h_ */
