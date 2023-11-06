/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
pinf:
	.long	0x7F800000

onehalf:
	.float	0.5

	.globl	_sinhl
_sinhl:

/* long double sinhl(long double x)

	The textbook formula

		sinh(x) = 0.5*(exp(x) - exp(-x))

	has loss of precision for small x.	To avoid these
	problems, if we let y = expm1(|x|) = exp(x|) - 1., where expm1() is
	evaluated using a built-in x87 coprocessor function, we can write the
	hyperbolic sine for positive arguments as

		sinh(x) = 0.5*(y/(y+1.) + y)

	which has no problems with loss of precision.  Large arguments are
	handled separately to increase speed in those ranges.

	The ranges are split and computed as follows:

		sinh(x) = -inf,			x = [-inf, -710]
		sinh(x) = -0.5*(y/(y+1.) + y),	x = <-710, 0>
		sinh(x) =  0.5*(y/(y+1.) + y),	x = [0, 710>
		sinh(x) = inf,			x = [710, +inf]

	errno is set as follows:

	0 = normal completion
	1 = input is NaN
	2 = output is infinite

	*/
	movl	12(%esp), %eax
	movl	%eax, %edx		/* Save for later use. */

	andl	$0x00007FFF, %eax
	cmpl	$0x00007FFF, %eax
	je	abarg
	cmp	$0x00004007, %eax
	ja	alt_formula

argok:
	fldt	4(%esp)
	fabs
	fldl2e				/* log2(e)   x			  */
	fmulp				/* xs				  */
	fld	%st			/* xs	     xs			  */
	frndint				/* nint(xs)  xs			  */
	fxch	%st(1)			/* xs	     nint		  */
	fsub	%st(1), %st		/* fract     nint		  */
	f2xm1				/* exps-1    nint		  */
	fxch	%st(1)			/* nint	     exps-1		  */
	fld1				/* 1	     nint    exps-1	  */
	fscale				/* scale     nint    exps-1	  */
	fld1				/* 1	     scale   nint  exps-1 */
	/* Should be fsubp %st, %st(1) (gas bug) */
	.byte	0xDE, 0xE9		/* scale-1   nint    exps-1	  */
	fxch	%st(2)			/* exps-1    nint    scale-1	  */
	fscale				/* expm	     nint    scale-1	  */
	fstp	%st(1)			/* exp	     scale-1		  */
	faddp				/* y=exp-1			  */
	fld1				/* 1	     y			  */
	fadd	%st(1), %st		/* y+1	     y			  */
	fdivr	%st(1), %st		/* y/(y+1)   y			  */
	faddp				/* y+y/(y+1)			  */
	fmuls	onehalf

dosign:
	testl	$0x00008000, %edx	/* Fix up sign. */
	jz	return
	fchs

return:
	ret

alt_formula:

	/* 0x0.B174DDC031AEC0E8p+14 */
	movl	4(%esp), %eax
	movl	8(%esp), %edx
	mov	12(%esp), %ecx
	and	$0x7FFFFFFF, %edx	/* Ignore the unused significand bit */
	and	$0x00007FFF, %ecx
	cmpl	$0x31AEC0E8, %eax
	sbbl	$0x3174DDC0, %edx
	sbbl	$0x0000400C, %ecx
	jge	bigarg

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
	jmp	dosign

bigarg:
	movl	$2, _errno
	jmp	argok			/* let it overflow */

infarg:
	flds	pinf
	jmp	dosign

abarg:
	movl	8(%esp), %eax		/* inf or NaN */
	and	$0x7FFFFFFF, %eax	/* Ignore the unused significand bit */
	orl	4(%esp), %eax
	jz	infarg

badarg:					/* arg is NaN */
	fldt	4(%esp)
	ret
