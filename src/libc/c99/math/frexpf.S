/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

onehalf:
	.float	0.5

	.globl	_frexpf
_frexpf:

	/* float frexpf(float value, int *expon);

	returns mantissa in range [0.5, 1), exponent such that
	value = mantissa * (2^expon)
	*/

	movl	8(%esp), %edx		/* Load pointer to expon. */

	movl	4(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	jz	zeroinfnan		/* x is zero */

	cmpl	$0x7F800000, %eax
	jge	zeroinfnan		/* x is inf or NaN */

argok:
	flds	4(%esp)
	fxtract
	flds	onehalf
	fmulp

	fxch
	fistpl	(%edx)
	incl	(%edx)
	ret

zeroinfnan:				/* arg is zero, inf or NaN */
	movl	$0, (%edx)
	flds	4(%esp)
	ret
