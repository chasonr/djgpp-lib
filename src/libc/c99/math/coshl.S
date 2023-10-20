/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
pinf:
	.long	0x7F800000

NaN:
	.long	0xFFC00000

onehalf:
	.float	0.5

	.globl	_coshl
_coshl:

/* long double cosh(long double x)

	If we let y = exp(|x|), the function is computed as

		cosh(x) = 0.5*(y + 1./y)

	For large |x|, the 1/y term is insignificant; avoid premature
	overflow by computing:

		cosh(x) = exp(|x| - log(2.0))

	The absolute value is included to ensure that the identity

		cosh(x) = cosh(-x)

	is satisfied exactly.

	errno is set as follows:

	0 = normal completion
	1 = input is NaN
	2 = output is infinite

	*/
	movl	12(%esp), %eax
	andl	$0x00007FFF, %eax
	cmpl	$0x00007FFF, %eax
	je	abarg
	cmp	$0x00004007, %eax
	ja	alt_formula

argok:
	fldt	4(%esp)
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

alt_formula:

	/* 0x0.B174DDC031AEC0E8p+14 */
	movl	4(%esp), %eax
	cmpl	$0x31AEC0E8, %eax
	movl	8(%esp), %eax
	and	$0x7FFFFFFF, %eax	/* Ignore the unused significand bit */
	subl	$0x3174DDC0, %eax
	mov	12(%esp), %eax
	and	$0x00007FFF, %eax
	subl	$0x0000400C, %eax
	jg	bigarg

	fldt	4(%esp)
	fldl2e				/* log2(e)   x		   */
	fmulp				/* log2(e)*x		   */
	fld1
	fsubrp				/* l=log2(e)*x-1	   */
	fld	%st			/* l l			   */
	frndint				/* int(l) l		   */
	fxch				/* l int(l)		   */
	fsub	%st(1)			/* frac(l) int(l)	   */
	f2xm1				/* 2**frac(l)-1 int(l)	   */
	fld1				/* 1 2**frac(l)-1 int(l)   */
	faddp				/* 2**frac(l) int(l)	   */
	fscale				/* 2**l int(l)		   */
	fstp	%st(1)			/* 2**l			   */
	ret

bigarg:
	movl	$2, _errno
	jmp	argok			/* let it overflow */

infarg:
	flds	pinf
	ret

abarg:
	movl	8(%esp), %eax		/* inf or NaN */
	and	$0x7FFFFFFF, %eax	/* Ignore the unused significand bit */
	orl	4(%esp), %eax
	jz	infarg

badarg:					/* arg is NaN */
	movl	$1, _errno
	flds	NaN
	ret
