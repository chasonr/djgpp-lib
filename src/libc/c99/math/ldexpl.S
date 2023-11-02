/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.text
	.globl	_ldexpl
_ldexpl:

	/* long double ldexpl(long double x, int expon);
		result = x * (2^expon)
	*/

	movl	12(%esp), %eax		/* Get high word of x */
	andl	$0x00007FFF, %eax
	jz	maybezero		/* x may be zero */
	cmpl	$0x00007FFF, %eax
	je	zeroinfnan		/* x = INF or NaN */

argok:
	fildl	16(%esp)
	fldt	4(%esp)
	fscale
	fstp	%st(1)

	/* Check for overflow and underflow */
	fxam
	fnstsw	%ax
	andb	$0x45, %ah		/* Get the C3, C2 and C0 bits */
	cmpb	$0x05, %ah		/* infinity */
	je	RangeError
	cmpb	$0x40, %ah		/* zero */
	je	RangeError

	ret

maybezero:
	movl	4(%esp), %eax
	orl	8(%esp), %eax
	jnz	argok
	/* else fall through */

zeroinfnan:				/* zero, inf or NaN */
	fldl	4(%esp)
	ret

RangeError:
	movl	$2, _errno
	ret
