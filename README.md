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

Many functions in math.h have two versions. The one defined in libc.a is
coded specifically for the x87 unit and sets errno on any math errors.
The one defined in libm.a is more generically coded, and may set errno
or call matherr() on error. See the file info/libc.info for details.

| __Function__ | __float__      | __double__     | __long double__ |
|--------------|----------------|----------------|-----------------|
| `acos`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `acosh`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `asin`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `asinh`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `atan`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `atan2`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `atanh`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `cbrt`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `ceil`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `copysign`   | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `cos`        | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `cosh`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `erf`        | libm.a         | libm.a         | _missing_       |
| `erfc`       | libm.a         | libm.a         | _missing_       |
| `exp`        | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `exp2`       | libc.a         | libc.a         | libc.a          |
| `expm1`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `fabs`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `fdim`       | libc.a         | libc.a         | libc.a          |
| `floor`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `fma`        | libc.a         | libc.a         | libc.a          |
| `fmax`       | libc.a         | libc.a         | libc.a          |
| `fmin`       | libc.a         | libc.a         | libc.a          |
| `fmod`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `frexp`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `hypot`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `ilogb`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `ldexp`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `lgamma`     | libm.a         | libm.a         | _missing_       |
| `llrint`     | libc.a, libm.a | libc.a, libm.a | libc.a, libm.a  |
| `llround`    | libc.a, libm.a | libc.a, libm.a | libc.a, libm.a  |
| `log`        | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `log10`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `log1p`      | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `log2`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `logb`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `lrint`      | libc.a, libm.a | libc.a, libm.a | libc.a, libm.a  |
| `lround`     | libc.a, libm.a | libc.a, libm.a | libc.a, libm.a  |
| `modf`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `nan`        | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `nearbyint`  | libc.a         | libc.a         | libc.a          |
| `nextafter`  | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `nexttoward` | libc.a         | libc.a         | libc.a          |
| `pow`        | libm.a         | libc.a, libm.a | _missing_       |
| `remainder`  | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `remquo`     | libc.a         | libc.a         | libc.a          |
| `rint`       | libc.a, libm.a | libc.a, libm.a | libc.a, libm.a  |
| `round`      | libc.a, libm.a | libc.a, libm.a | libc.a, libm.a  |
| `scalbln`    | libc.a         | libc.a         | libc.a          |
| `scalbn`     | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `sin`        | libm.a         | libc.a, libm.a | _missing_       |
| `sinh`       | libm.a         | libc.a, libm.a | _missing_       |
| `sqrt`       | libc.a, libm.a | libc.a, libm.a | libc.a          |
| `tan`        | libm.a         | libc.a, libm.a | _missing_       |
| `tanh`       | libm.a         | libc.a, libm.a | _missing_       |
| `tgamma`     | _missing_      | _missing_      | _missing_       |
| `trunc`      | libm.a         | libm.a         | libm.a          |

libm.a implements additional functions not present in C11:

| __Function__  | __float__ | __double__ | __long double__ |
|---------------|-----------|------------|-----------------|
| `cabs`        | libm.a    | libm.a     | _missing_       |
| `drem`        | libm.a    | libm.a     | _missing_       |
| `finite`      | libm.a    | libm.a     | libm.a          |
| `gamma`       | libm.a    | libm.a     | _missing_       |
| `gamma_r`     | libm.a    | libm.a     | _missing_       |
| `infinity`    | libm.a    | libm.a     | _missing_       |
| `isinf`       | libm.a    | libm.a     | libm.a          |
| `isnan`       | libm.a    | libm.a     | libm.a          |
| `j0`          | libm.a    | libm.a     | _missing_       |
| `j1`          | libm.a    | libm.a     | _missing_       |
| `jn`          | libm.a    | libm.a     | _missing_       |
| `lgamma_r`    | libm.a    | libm.a     | _missing_       |
| `scalb`       | libm.a    | libm.a     | _missing_       |
| `significand` | libm.a    | libm.a     | _missing_       |
| `y0`          | libm.a    | libm.a     | _missing_       |
| `y1`          | libm.a    | libm.a     | _missing_       |
| `yn`          | libm.a    | libm.a     | _missing_       |

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
