/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

onehalf:
	.float	0.5

	.globl	_frexp
_frexp:

	/* double frexp(double value, int *expon);

	returns mantissa in range [0.5, 1), exponent such that
	value = mantissa * (2^expon)
	*/
	
	movl	12(%esp), %edx		/* Load pointer to expon. */

	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	jz	maybezero		/* arg might be 0 */

	cmpl	$0x7FF00000, %eax
	jge	zeroinfnan		/* arg is inf or NaN */

argok:
	fldl	4(%esp)
	fxtract
	flds	onehalf
	fmulp

	fxch
	fistpl	(%edx)
	incl	(%edx)
	ret

maybezero:				/* arg may be zero */
	movl	4(%esp), %eax
	testl	%eax, %eax
	jnz	argok			/* arg is not zero */

zeroinfnan:				/* arg is zero, inf or NaN */
	movl	$0, (%edx)
	fldl	4(%esp)
	ret
