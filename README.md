This repository continues development of the DJGPP run time library.

The original source is available from any mirror of DJGPP as the archives
djcrx205.zip, djlsr205.zip and djtzs205.zip.

Goals
=====

Goals of this project are:

* to fix any bugs that might be found
* to support all of C11
* to support as much of Posix as is practical in a DOS environment
* to support the GCC `\_FORTIFY\_SOURCE` facility

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

Headers completely supported
----------------------------
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
assert.h:
* no `static\_assert`

float.h:
* `DECIMAL\_DIG` missing
* `FLT\_EVAL\_METHOD` missing
* `{FLT,DBL,LDBL}\_HAS\_SUBNORM` missing
* `{FLT,DBL,LDBL}\_DECIMAL\_DIG` missing
* `{FLT,DBL,LDBL}\_TRUE\_MIN` missing

inttypes.h
* `wcstoimax` missing
* `wcstoumax` missing

limits.h
* Wrongly defines `WCHAR\_MIN`, `WCHAR\_MAX`, `WINT\_MIN` and `WINT\_MAX`
* Defines `LLONG\_MIN`, `LLONG\_MAX` and `ULLONG\_MAX` only if not `\_POSIX\_SOURCE`

math.h
* `float\_t` and `double\_t` missing
* `FP\_ILOGB0` and `FP\_ILOGBNAN` missing
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

stdarg.h:
* `va\_copy` missing

stddef.h:
* `max\_align\_t` missing

stdio.h:
* all items present, but check `printf`/`scanf`

stdlib.h
* `aligned\_alloc` missing
* `at\_quick\_exit` missing
* `quick\_exit` missing

time.h
* `TIME\_UTC` missing
* `struct timespec` missing
* `timespec\_get` missing

wchar.h
* wrongly includes stddef.h
* `struct tm` missing
* all functions missing

wctype.h
* all functions missing

Missing headers
---------------
* fenv.h
* complex.h
* iso646.h
* stdalign.h
* stdatomic.h
* stdnoreturn.h
* tgmath.h
* uchar.h
