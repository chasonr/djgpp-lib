/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
NaN:
	.long	0xFFC00000

pinf:
	.long	0x7F800000

	.globl	_expm1f
_expm1f:
	movl	4(%esp), %eax		/* Test for special cases. */
	movl	%eax, %edx
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7F800000, %eax
	je	infarg
	ja	badarg
	xorl	$0x80000000, %edx
	cmpl	$0xC2B17218, %edx
	jae	bigarg			/* normal args: */
					/* 0 < |x| <= log(FLT_MAX) */
argok:					/* N.B. */
					/* log(FLT_MAX) = 0x42B17218 */
	flds	4(%esp)
	fldl2e				/* log2(e)  x			   */
	fmulp				/* xs				   */
	fld	%st			/* xs	    xs			   */
	frndint				/* nint(xs) xs			   */
	fxch	%st(1)			/* xs	    nint		   */
	fsub	%st(1), %st		/* fract    nint		   */
	f2xm1				/* exps-1   nint		   */
	fxch	%st(1)			/* nint	    exps-1		   */
	fld1				/* 1	    nint    exps-1	   */
	fscale				/* scale    nint    exps-1	   */
	fld1				/* 1	    scale   nint    exps-1 */
	/* Should be fsubp %st,%st(1) (gas bug) */
	.byte	0xDE, 0xE9		/* scale-1  nint    exps-1	   */
	fxch	%st(2)			/* exps-1   nint    scale-1	   */
	fscale				/* expm	    nint    scale-1	   */
	fstp	%st(1)			/* exp	    scale-1		   */
	faddp				/* exp-1			   */
	ret

bigarg:
	movl	$2, _errno		/* |x| is really big, but finite */
	jmp	argok

infarg:					/* |x| = inf */
	testl	$0x80000000, 4(%esp)
	jz	posinf

neginf:
	fld1
	fchs
	ret

posinf:
	flds	pinf
	ret

badarg:					/* arg is NaN */
	movl	$1, _errno
	flds	NaN
	ret
