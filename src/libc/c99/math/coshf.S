/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
pinf:
	.long	0x7F800000

onehalf:
	.float	0.5

	.globl	_coshf
_coshf:

/* float cosh(float x)

	If we let y = exp(|x|), the function is computed as

		cosh(x) = 0.5*(y + 1./y)

	The absolute value is included to ensure that the identity

		cosh(x) = cosh(-x)

	is satisfied exactly.

	errno is set as follows:

	0 = normal completion
	1 = input is NaN
	2 = output is infinite

	*/
	movl	4(%esp), %eax

	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7F800000, %eax
	je	infarg
	jg	badarg
	cmpl	$0x42B2D4FC, %eax
	jg	bigarg

argok:
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
	fstp	%st(1)			/* y=exp		   */
	fld1				/* 1	     y		   */
	fdiv	%st(1), %st		/* 1/y	     y		   */
	faddp				/* y+1/y		   */
	fmuls	onehalf
	ret

bigarg:
	movl	$2, _errno
	jmp	argok			/* let it overflow */

infarg:
	flds	pinf
	ret

badarg:					/* arg is NaN */
	flds	4(%esp)
	ret
