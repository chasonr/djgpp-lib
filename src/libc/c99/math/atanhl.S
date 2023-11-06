/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
LC0:
	.float	0f0.5

	.globl	_atanhl
_atanhl:
	/* long double atanhl(long double x)

	The textbook formula

		atanh(x) = 0.5*ln((1.+x)/(1.-x))

	has loss of precision for small x.  To avoid these
	problems, we split the range by computing

		atanh(x) = -atanh(-x)

	for negative x.	 The textbook formula still involves cancellation, but
	by letting log1p(x) = log(1+x), a built-in x87 coprocessor function, we
	can write the arc tanh as

		atanh(x) = 0.5*log1p(2.*x/(1.-x))

	which has no problems with loss of precision.
	*/
					/* atanh(x) */

	movl	12(%esp), %eax		/* is x >= 1? */
	movl	%eax, %ecx
	andl	$0x00007FFF, %eax	/* |x| */
	cmpl	$0x00007FFF, %eax
	je	abarg
	cmpl	$0x00003FFF, %eax
	jg	badarg			/* |x| >= 2 or x = inf or NaN */
	je	onetotwo		/* 1 <= |x| < 2 */

argok:
	fldln2				/* ln2 */
	fmuls	LC0
	fldt	4(%esp)			/* x   ln2 */
	ftst
	fnstsw	%ax
	sahf
	fabs				/* |x|	       */
	fld1				/* 1   x   ln2 */
	fsub	%st(1),%st		/* 1-x x   ln2 */
	/* Should be fdivp %st, %st(1) (gas bug) */
	.byte	0xDE, 0xF9		/* quo ln2     */
	fadd	%st, %st		/* arg	       */
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x3FC5F619, %eax
	jbe	1f
	fld1
	faddp
	fyl2x				/* logi(x) */
	jmp 2f
1:
	fyl2xp1				/* log1pi(x) */
2:
	testl	$0x8000, %ecx		/* test for sign bit */
	je	3f
	fchs
3:
	ret

onetotwo:
	movl	8(%esp), %eax		/* is x = +/-1? */
	andl	$0x7FFFFFFF, %eax	/* ignore the unused significand bit */
	orl	4(%esp), %eax
	jnz	badarg

infarg:
	movl	$2, _errno
	fldz
	fldt	4(%esp)
	fdivp
	ret

	/* Intentionally raise the "invalid" exception */
badarg:
	movl	$1, _errno
	fld1
	fchs
	fsqrt
	ret

abarg:					/* Infinity or NaN */
	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax	/* ignore the unused significand bit */
	orl	4(%esp), %eax
	jz	badarg			/* Infinity */

nanarg:
	fldt	4(%esp)
	ret
