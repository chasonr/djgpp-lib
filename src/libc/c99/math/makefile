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

include $(TOP)/../makefile.inc

fpclassf.S: fp-asm.h

fpclassd.S: fp-asm.h

fpclassl.S: fp-asm.h

fp-asm.h: fp-asm.sed $(TOP)/../../include/math.h
	sed -n -f fp-asm.sed $(TOP)/../../include/math.h > fp-asm.h

clean::
	$(MISC) rm fp-asm.h
