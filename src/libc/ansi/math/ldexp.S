/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.text
	.globl	_ldexp
_ldexp:

	/* double ldexp(double x, int expon);
		result = x * (2^expon)
	*/

	movl	8(%esp), %eax		/* Get high word of x */
	andl	$0x7FFFFFFF, %eax
	jz	maybezero		/* x may be zero */
	cmpl	$0x7FF00000, %eax
	jge	zeroinfnan		/* x = INF or NaN */

argok:
	fildl	12(%esp)
	fldl	4(%esp)
	fscale
	fstp	%st(1)

	/* Check for overflow and underflow */
	subl	$8, %esp
	fstpl	(%esp)
	fldl	(%esp)
	addl	$8, %esp
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
	test	%eax, %eax
	jnz	argok
	/* else fall through */

zeroinfnan:				/* zero, inf or NaN */
	fldl	4(%esp)
	ret

RangeError:
	movl	$2, _errno
	ret
