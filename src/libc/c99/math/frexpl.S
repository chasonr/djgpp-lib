/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

onehalf:
	.float	0.5

	.globl	_frexpl
_frexpl:

	/* long double frexpl(long double value, int *expon);

	returns mantissa in range [0.5, 1), exponent such that
	value = mantissa * (2^expon)
	*/
	
	movl	16(%esp), %edx		/* Load pointer to expon. */

	movl	12(%esp), %eax
	andl	$0x00007FFF, %eax	/* Is x = 0 ? */
	jz	maybezero

	cmpl	$0x00007FFF, %eax
	je	zeroinfnan		/* +/- inf or NaN */

argok:
	fldt	4(%esp)
	fxtract
	flds	onehalf
	fmulp

	fxch
	fistpl	(%edx)
	incl	(%edx)
	ret

maybezero:				/* x is zero or subnormal */
	movl	8(%esp), %eax
	orl	4(%esp), %eax
	jnz	argok			/* x is subnormal */
	
zeroinfnan:				/* arg is zero, inf or NaN */
	movl	$0, (%edx)
	fldt	4(%esp)
	ret
