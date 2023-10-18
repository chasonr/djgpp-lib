This repository continues development of the DJGPP run time library.

The original source is available from any mirror of DJGPP as the archives
djcrx205.zip, djlsr205.zip and djtzs205.zip.

Goals
=====

Goals of this project are:

* to fix any bugs that might be found
* to support all of C11
* to support as much of Posix as is practical in a DOS environment
* to support the GCC `_FORTIFY_SOURCE` facility

How to build
============

I am cross-compiling from Linux Mint using a compiler built from the Github
repository https://github.com/andrewwutw/build-djgpp.git . Building natively does
not seem to work, at least on FreeDOS; the make utility crashes for no apparent
reason. I have not yet tried it on real MS-DOS.

Use "make" to build. Use "make zip" to create djdev206.zip and djtzn206.zip;
use these in your DJGPP installation, whether native or a cross-compiler, in
place of the corresponding original archives.

Current status of C11 support
=============================

The original djlsr205 supports C90 with a few C99 features. Here is the current
support for C11:

Headers provided by GCC
-----------------------
* float.h
* iso646.h
* limits.h
* stdalign.h
* stdarg.h
* stdatomic.h
* stddef.h
* stdnoreturn.h
* tgmath.h

Headers completely supported
----------------------------
* assert.h
* ctype.h
* errno.h
* fenv.h
* inttypes.h
* locale.h
* setjmp.h
* signal.h
* stdbool.h
* stdint.h
* stdio.h
* string.h
* wctype.h

Headers partially or incorrectly supported
------------------------------------------
math.h
* in progress
* implemented:
  * `acos`, `acosf`
  * `acosh`, `acoshf`
  * `asin`, `asinf`
  * `asinh`, `asinhf`
  * `atan2`, `atan2f`
  * `atan`, `atanf`
  * `atanh`, `atanhf`
  * `cbrt`, `cbrtf`
  * `ceil`, `ceilf`
  * `copysign`, `copysignf`
  * `cos`, `cosf`
  * `cosh`, `coshf`
  * `erf`, `erff`
  * `erfc`, `erfcf`
  * `exp`, `expf`
  * `exp2`
  * `expm1`, `expm1f`
  * `fabs`, `fabsf`
  * `floor`, `floorf`
  * `fmod`, `fmodf`
  * `frexp`, `frexpf`
  * `hypot`, `hypotf`
  * `ilogb`, `ilogbf`
  * `ldexp`, `ldexpf`
  * `lgamma`, `lgammaf`
  * `llrint`, `llrintf`, `llrintl`
  * `llround`, `llroundf`, `llroundl`
  * `log10`, `log10f`
  * `log1p`, `log1pf`
  * `log2`, `log2f`
  * `log`, `logf`
  * `logb`, `logbf`
  * `lrint`, `lrintf`, `lrintl`
  * `lround`, `lroundf`, `lroundl`
  * `modf`, `modff`
  * `nan`, `nanf`
  * `nextafter`, `nextafterf`
  * `pow`, `powf`
  * `remainder`, `remainderf`
  * `rint`, `rintf`, `rintl`
  * `round`, `roundf`, `roundl`
  * `scalbn`, `scalbnf`
  * `sin`, `sinf`
  * `sinh`, `sinhf`
  * `sqrt`, `sqrtf`
  * `tan`, `tanf`
  * `tanh`, `tanhf`
  * `trunc`, `truncf`, `truncl`
* missing:
  * `acoshl`
  * `acosl`
  * `asinhl`
  * `asinl`
  * `atan2l`
  * `atanhl`
  * `atanl`
  * `cbrtl`
  * `ceill`
  * `copysignl`
  * `coshl`
  * `cosl`
  * `erfcl`
  * `erfl`
  * `exp2f`, `exp2l`
  * `expl`
  * `expm1l`
  * `fabsl`
  * `fdim`, `fdimf`, `fdiml`
  * `floorl`
  * `fma`, `fmaf`, `fmal`
  * `fmax`, `fmaxf`, `fmaxl`
  * `fmin`, `fminf`, `fminl`
  * `fmodl`
  * `frexpl`
  * `hypotl`
  * `ilogbl`
  * `ldexpl`
  * `lgammal`
  * `log10l`
  * `log1pl`
  * `log2l`
  * `logbl`
  * `logl`
  * `modfl`
  * `nanl`
  * `nearbyint`, `nearbyintf`, `nearbyintl`
  * `nextafterl`
  * `nexttoward`, `nexttowardf`, `nexttowardl`
  * `powl`
  * `remainderl`
  * `remquo`, `remquof`, `remquol`
  * `scalbln`, `scalblnf`, `scalblnl`
  * `scalbnl`
  * `sinhl`
  * `sinl`
  * `sqrtl`
  * `tanhl`
  * `tanl`
  * `tgamma`, `tgammaf`, `tgammal`

stdlib.h
* `aligned_alloc` missing
* `at_quick_exit` missing
* `quick_exit` missing

time.h
* `TIME_UTC` missing
* `struct timespec` missing
* `timespec_get` missing

wchar.h
* in progress
* implemented:
  * `wmemcpy`
  * `wmemmove`
  * `wmemcmp`
  * `wmemchr`
  * `wmemset`
  * `wcscat`
  * `wcschr`
  * `wcscmp`
  * `wcscpy`
  * `wcscspn`
  * `wcslen`
  * `wcsncat`
  * `wcsncmp`
  * `wcsncpy`
  * `wcspbrk`
  * `wcsrchr`
  * `wcsspn`
  * `wcsstr`
  * `wcstok`
  * `wcstod`
  * `wcstof`
  * `wcstol`
  * `wcstold`
  * `wcstoll`
  * `wcstoul`
  * `wcstoull`
  * `wcsftime`
  * `btowc`
  * `mbrlen`
  * `mbrtowc`
  * `mbsinit`
  * `mbsrtowcs`
  * `wcrtomb`
  * `wcsrtombs`
  * `wctob`
* partially implemented:
  * `wcscoll` -- same as `wcscmp`, no locale-dependent behavior
  * `wcsxfrm` -- identity map, no locale-dependent behavior
* missing:
  * `fgetwc`
  * `fgetws`
  * `fputwc`
  * `fputws`
  * `fwide`
  * `fwprintf`
  * `fwscanf`
  * `getwc`
  * `getwchar`
  * `putwc`
  * `putwchar`
  * `swprintf`
  * `swscanf`
  * `ungetwc`
  * `vfwprintf`
  * `vfwscanf`
  * `vswprintf`
  * `vswscanf`
  * `vwprintf`
  * `vwscanf`
  * `wprintf`
  * `wscanf`

Missing headers
---------------
* complex.h
* uchar.h
