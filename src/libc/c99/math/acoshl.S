/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
NaN:
	.long	0xFFC00000

	.text
	.globl	_acoshl
_acoshl:

	/* long double acoshl(long double x) {
	The textbook formula

	acosh(x) = ln(x + sqrt(x*x - 1.))

	has cancellation for x near 1.	To avoid this problem, let y = x - 1.,
	and let log1p(x) = log(1+x), a built-in x87 coprocessor function.  Then

	acosh(x) = log1p(y + sqrt(y*(y+2.)))

	*/

	subl	$4, %esp

	movl	16(%esp), %eax # is x < 1?
	andl	$0x0000FFFF, %eax
	cmpl	$0x00003FFF, %eax
	jl	badarg
	cmpl	$0x00007FFF, %eax	/* Control flows straight through for */
	ja	badarg			/* normal args 1 <= x < +inf */
	je	abarg

argok:
	fldln2				/* ln2		     */
	fldt	8(%esp)			/* x	 ln2	     */
	fld	%st			/* x	 x   ln2     */
	fld1				/* 1	 x   x	 ln2 */
	/* Should be fsubp %st, %st(1) (gas bug) */
	.byte	0xDE, 0xE9		/* x-1	 x   ln2     */
	fxch	%st(1)			/* x	 x-1 ln2     */
	fld1				/* 1	 x   x-1 ln2 */
	faddp				/* x+1	 x-1 ln2     */
	fmul	%st(1), %st		/* x*x-1 x-1 ln2     */
	fsqrt				/* sqrt	 x-1 ln2     */
	faddp				/* arg	 ln2	     */
	fsts	(%esp)
	movl	(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x3E95F61A, %eax	/* 1 - sqrt(0.5) */
	jbe	1f
	fld1
	faddp
	fyl2x				/* logi(x) */
	addl	$4, %esp
	ret

1:					/* log1pi(x) */
	fyl2xp1
	addl	$4, %esp
	ret

abarg:
	movl	12(%esp), %eax		/* inf or NaN */
	andl	$0x7FFFFFFF, %eax	/* ignore unused significand bit */
	orl	8(%esp), %eax
	jz	argok

badarg:
	movl	$1, _errno
	flds	NaN
	addl	$4, %esp
	ret
