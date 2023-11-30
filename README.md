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
  * complex.h with conformance to Annex G
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
  * stdlib.h
  * string.h
  * time.h
  * uchar.h
  * wctype.h

Headers partially or incorrectly supported
------------------------------------------
math.h

Many functions in math.h have two versions. The one defined in libc.a is
coded specifically for the x87 unit and sets errno on any math errors.
The one defined in libm.a is more generically coded, and may set errno
or call matherr() on error. See the file info/libc.info for details.

All functions currently implemented in libc.a and libm.a, and defined in
C11, pass a number of tests for conformance to Annex F of the C11 standard,
provided that `_LIB_VERSION` is set to `_IEEE_`.  `_IEEE_` is now the
default; in the original library, the default is `_XOPEN_`, contrary to
what info/libc.info says.

All math functions defined in C11 are now present in libc.a.  The ones
present in libm.a are listed below.

| __Function__  | __float__ | __double__ | __long double__ |
|---------------|-----------|------------|-----------------|
| `acos`        | libm.a    | libm.a     | _missing_       |
| `acosh`       | libm.a    | libm.a     | _missing_       |
| `asin`        | libm.a    | libm.a     | _missing_       |
| `asinh`       | libm.a    | libm.a     | _missing_       |
| `atan`        | libm.a    | libm.a     | _missing_       |
| `atan2`       | libm.a    | libm.a     | _missing_       |
| `atanh`       | libm.a    | libm.a     | _missing_       |
| `cbrt`        | libm.a    | libm.a     | _missing_       |
| `ceil`        | libm.a    | libm.a     | _missing_       |
| `copysign`    | libm.a    | libm.a     | _missing_       |
| `cos`         | libm.a    | libm.a     | _missing_       |
| `cosh`        | libm.a    | libm.a     | _missing_       |
| `erf`         | libm.a    | libm.a     | libm.a          |
| `erfc`        | libm.a    | libm.a     | libm.a          |
| `exp`         | libm.a    | libm.a     | _missing_       |
| `exp2`        | _missing_ | _missing_  | _missing_       |
| `expm1`       | libm.a    | libm.a     | _missing_       |
| `fabs`        | libm.a    | libm.a     | _missing_       |
| `fdim`        | _missing_ | _missing_  | _missing_       |
| `floor`       | libm.a    | libm.a     | _missing_       |
| `fma`         | _missing_ | _missing_  | _missing_       |
| `fmax`        | _missing_ | _missing_  | _missing_       |
| `fmin`        | _missing_ | _missing_  | _missing_       |
| `fmod`        | libm.a    | libm.a     | _missing_       |
| `frexp`       | libm.a    | libm.a     | _missing_       |
| `hypot`       | libm.a    | libm.a     | _missing_       |
| `ilogb`       | libm.a    | libm.a     | _missing_       |
| `ldexp`       | libm.a    | libm.a     | _missing_       |
| `lgamma`      | libm.a    | libm.a     | libm.a          |
| `llrint`      | libm.a    | libm.a     | libm.a          |
| `llround`     | libm.a    | libm.a     | libm.a          |
| `log`         | libm.a    | libm.a     | _missing_       |
| `log10`       | libm.a    | libm.a     | _missing_       |
| `log1p`       | libm.a    | libm.a     | _missing_       |
| `log2`        | libm.a    | libm.a     | _missing_       |
| `logb`        | libm.a    | libm.a     | _missing_       |
| `lrint`       | libm.a    | libm.a     | libm.a          |
| `lround`      | libm.a    | libm.a     | libm.a          |
| `modf`        | libm.a    | libm.a     | _missing_       |
| `nan`         | libm.a    | libm.a     | _missing_       |
| `nearbyint`   | _missing_ | _missing_  | _missing_       |
| `nextafter`   | libm.a    | libm.a     | _missing_       |
| `nexttoward`  | _missing_ | _missing_  | _missing_       |
| `pow`         | libm.a    | libm.a     | _missing_       |
| `remainder`   | libm.a    | libm.a     | _missing_       |
| `remquo`      | _missing_ | _missing_  | _missing_       |
| `rint`        | libm.a    | libm.a     | libm.a          |
| `round`       | libm.a    | libm.a     | libm.a          |
| `scalbln`     | _missing_ | _missing_  | _missing_       |
| `scalbn`      | libm.a    | libm.a     | _missing_       |
| `sin`         | libm.a    | libm.a     | _missing_       |
| `sinh`        | libm.a    | libm.a     | _missing_       |
| `sqrt`        | libm.a    | libm.a     | _missing_       |
| `tan`         | libm.a    | libm.a     | _missing_       |
| `tanh`        | libm.a    | libm.a     | _missing_       |
| `tgamma`      | libm.a    | libm.a     | libm.a          |
| `trunc`       | libm.a    | libm.a     | libm.a          |

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

wchar.h

  * All functions at least minimally implemented
  * No locale support in:
    * `wcscoll` -- same as `wcscmp`, no locale-dependent behavior
    * `wcsxfrm` -- identity map, no locale-dependent behavior

Status of `_FORTIFY_SOURCE` support
===================================

The following functions provide additional boundary checking if
`_FORTIFY_SOURCE` is in effect:
  * Buffer overruns trigger a message to stderr and an abort.
  * if `_FORTIFY_SOURCE` is at least 2, printf-like functions may not use
    the %n format specifier when the format string is not constant. This
    does not apply to vprintf-like functions, because they are typically
    used with wrappers to make new printf-like functions.

string.h

  * memcpy
  * memmove
  * memset
  * strcat
  * strcpy
  * strncat
  * strncpy
  * strxfrm
  * memccpy
  * stpcpy
  * stpncpy
  * strlcat
  * strlcpy

stdio.h

  * fgets
  * gets
  * fread
  * snprintf
  * sprintf
  * vsnprintf
  * vsprintf
  * fprintf
  * printf
  * dprintf
  * asprintf
  * asnprintf
  * vasnprintf

`gets` is furthermore marked as deprecated, and its use will trigger an error
if C11 or higher is in effect.

stdlib.h

  * mbstowcs
  * wcstombs
  * wctomb
  * realpath

wchar.h

  * wprintf
  * fwprintf
  * swprintf
  * vwprintf
  * vfwprintf
  * vswprintf
  * fgetws
  * wcscpy
  * wcsncpy
  * wcscat
  * wcsncat
  * wcsxfrm
  * wmemcpy
  * wmemmove
  * wmemset
  * wcsftime
  * wcrtomb
  * mbsrtowcs
  * wcsrtombs

unistd.h

  * confstr
  * getcwd
  * getgroups
  * read
  * gethostname
  * getwd
  * readlink
