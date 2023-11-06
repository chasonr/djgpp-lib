/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

pinf:
	.long	0x7F800000

	.globl	_expf
_expf:
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
	fldl2e				/* log2(e)   x		   */
	fmulp				/* log2(e)*x		   */
	fld	%st			/* xs	     xs		   */
	frndint				/* nint(xs)  xs		   */
	fxch	%st(1)			/* xs	     nint(xs)	   */
	fsub	%st(1), %st		/* fract     nint	   */
	f2xm1				/* exps()-1  nint	   */
	fld1				/* 1	     exps-1   nint */
	faddp				/* exps	     nint	   */
	fscale				/* exp	     nint	   */
	fstp	%st(1)			/* exp			   */
	ret

bigarg:
	movl	$2, _errno		/* |x| is really big, but finite */
	jmp	argok

infarg:					/* |x| = inf */
	testl	$0x80000000, 4(%esp)
	jz	posinf

neginf:
	fldz
	ret

posinf:
	flds	pinf
	ret

badarg:					/* arg is NaN */
	flds	4(%esp)
	ret
