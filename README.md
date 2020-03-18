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
repository https://github.com/dimkr/build-djgpp.git . Building natively does
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
* locale.h
* setjmp.h
* signal.h
* stdbool.h
* stdint.h
* string.h

Headers partially or incorrectly supported
------------------------------------------
inttypes.h
* `wcstoimax` missing
* `wcstoumax` missing

math.h
* `float_t` and `double_t` missing
* `FP_ILOGB0` and `FP_ILOGBNAN` missing
* All forms missing for some functions:
  * `scalbln{,f,l}`
  * `tgamma{,f,l}`
  * `nearbyint{,f,l}`
  * `remquo{,f,l}`
  * `fdim{,f,l}`
  * `fmax{,f,l}`
  * `fmin{,f,l}`
  * `fma{,f,l}`
  * `nexttoward{,f,l}`
* `exp2f` and `exp2l` missing
* Most long double functions missing:
  * `acosl`
  * `asinl`
  * `atanl`
  * `atan2l`
  * `cosl`
  * `sinl`
  * `tanl`
  * `acoshl`
  * `asinhl`
  * `atanhl`
  * `coshl`
  * `sinhl`
  * `tanhl`
  * `expl`
  * `expm1`
  * `frexpl`
  * `ilogbl`
  * `ldexpl`
  * `logl`
  * `log10l`
  * `log1pl`
  * `log2l`
  * `logbl`
  * `modfl`
  * `scalbnl`
  * `cbrtl`
  * `fabsl`
  * `hypotl`
  * `powl`
  * `sqrtl`
  * `erfl`
  * `erfcl`
  * `lgammal`
  * `ceill`
  * `floorl`
  * `fmodl`
  * `remainderl`
  * `copysignl`
  * `nextafterl`

stdio.h:
* all items present
* `printf` supports C11 features except for wide strings
* `scanf` needs to be checked

stdlib.h
* `aligned_alloc` missing
* `at_quick_exit` missing
* `quick_exit` missing

time.h
* `TIME_UTC` missing
* `struct timespec` missing
* `timespec_get` missing

wchar.h
* all functions missing

wctype.h
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
  * `wcstok`
* partially implemented:
  * `wcscoll` -- same as `wcscmp`, no locale-dependent behavior
  * `wcsxfrm` -- identity map, no locale-dependent behavior
* missing:
  * `btowc`
  * `fgetwc`
  * `fgetws`
  * `fputwc`
  * `fputws`
  * `fwide`
  * `fwprintf`
  * `fwscanf`
  * `getwc`
  * `getwchar`
  * `mbrlen`
  * `mbrtowc`
  * `mbsinit`
  * `mbsrtowcs`
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
  * `wcrtomb`
  * `wcsftime`
  * `wcsrtombs`
  * `wcsstr`
  * `wcstod`
  * `wcstof`
  * `wcstol`
  * `wcstold`
  * `wcstoll`
  * `wcstoul`
  * `wcstoull`
  * `wctob`
  * `wprintf`
  * `wscanf`

Missing headers
---------------
* fenv.h
* complex.h
* uchar.h
