# Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details
# Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details
# Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details
TOP=../..

SRC += errhandl.c
SRC += hugevalf.c
SRC += hugevall.c
SRC += lrintf.c
SRC += lrint.c
SRC += lrintl.c
SRC += llrintf.c
SRC += llrint.c
SRC += llrintl.c
SRC += nan_def.c
SRC += nan.c
SRC += nanf.c
SRC += nanl.c
SRC += fpclassf.S
SRC += fpclassd.S
SRC += fpclassl.S
SRC += sgnbitd.c
SRC += sgnbitf.c
SRC += sgnbitld.c

SRC += acosf.S
SRC += acosl.S
SRC += acoshf.S
SRC += acoshl.S
SRC += asinf.S
SRC += asinl.S
SRC += asinhf.S
SRC += asinhl.S
SRC += atanf.S
SRC += atanl.S
SRC += atan2f.S
SRC += atan2l.S
SRC += atanhf.S
SRC += atanhl.S
SRC += cbrtf.S
SRC += cbrtl.S
SRC += ceilf.S
SRC += ceill.S
SRC += copysignf.S
SRC += copysign.S
SRC += copysignl.S
SRC += cosf.S
SRC += cosl.S
SRC += coshf.S
SRC += coshl.S
SRC += expf.S
SRC += expl.S
SRC += exp2f.S
SRC += exp2l.S
SRC += expm1f.S
SRC += expm1l.S
SRC += fabsf.S
SRC += fabsl.S
SRC += fdimf.c
SRC += fdim.c
SRC += fdiml.c
SRC += floorf.S
SRC += floorl.S
SRC += fmaf.c
SRC += fma.c
SRC += fmal.c
SRC += bigfma.c
SRC += twosum.c
SRC += setodd.S
SRC += fmaxf.c
SRC += fmax.c
SRC += fmaxl.c
SRC += fminf.c
SRC += fmin.c
SRC += fminl.c
SRC += fmodf.S
SRC += fmodl.S
SRC += frexpf.S
SRC += frexpl.S
SRC += hypotf.S
SRC += hypotl.c
SRC += ilogbf.S
SRC += ilogb.S
SRC += ilogbl.S
SRC += ldexpf.S
SRC += ldexpl.S
SRC += llroundf.c
SRC += llround.c
SRC += llroundl.c
SRC += logf.S
SRC += logl.S
SRC += log10f.S
SRC += log10l.S
SRC += log1pf.S
SRC += log1pl.S
SRC += log2f.S
SRC += log2l.S
SRC += logbf.S
SRC += logb.S
SRC += logbl.S
SRC += lroundf.c
SRC += lround.c
SRC += lroundl.c
SRC += modff.S
SRC += nearbyintf.c
SRC += nearbyint.c
SRC += nearbyintl.c
SRC += nextafterf.c
SRC += nextafter.c
SRC += nextafterl.c
SRC += nexttowardf.c
SRC += nexttoward.c
SRC += nexttowardl.c
SRC += powf.c
SRC += powl.c
SRC += remainderf.S
SRC += remainder.S
SRC += remainderl.S
SRC += remquof.c
SRC += remquo.c
SRC += remquol.c
SRC += rintf.S
SRC += rint.S
SRC += rintl.S
SRC += roundf.c
SRC += round.c
SRC += roundl.c
SRC += scalblnf.c
SRC += scalbln.c
SRC += scalblnl.c
SRC += scalbnf.c
SRC += scalbn.c
SRC += scalbnl.c
SRC += sinf.S
SRC += sinl.S
SRC += sinhf.S
SRC += sinhl.S
SRC += sqrtf.S
SRC += sqrtl.S
SRC += tanf.S
SRC += tanl.S
SRC += tanhf.S
SRC += tanhl.S
SRC += truncf.S
SRC += trunc.S
SRC += truncl.S
SRC += derfc0l.c
SRC += erfcl.c
SRC += erfl.c
SRC += dgam1l.c
SRC += lgammal.c
SRC += tgammal.c
SRC += derfc0.c
SRC += erfc.c
SRC += erf.c
SRC += dgam1.c
SRC += lgamma.c
SRC += tgamma.c
SRC += tgammaf.c
SRC += lgammaf.c
SRC += erff.c
SRC += erfcf.c

include $(TOP)/../makefile.inc

fpclassf.S: fp-asm.h

fpclassd.S: fp-asm.h

fpclassl.S: fp-asm.h

fmaf.c: bigfma.h

fma.c: bigfma.h

fmal.c: bigfma.h

bigfma.c: bigfma.h

twosum.c: bigfma.h

fp-asm.h: fp-asm.sed $(TOP)/../../include/math.h
	sed -n -f fp-asm.sed $(TOP)/../../include/math.h > fp-asm.h

clean::
	$(MISC) rm fp-asm.h
