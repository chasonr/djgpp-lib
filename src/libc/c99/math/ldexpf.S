/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.text
	.globl	_ldexpf
_ldexpf:

	/* float ldexpf(float x, int expon);
		result = x * (2^expon)
	*/

	movl	4(%esp), %eax		/* Get x */
	andl	$0x7FFFFFFF, %eax
	jz	zeroinfnan		/* x = 0 */
	cmpl	$0x7F800000, %eax
	jge	zeroinfnan		/* x = INF or NaN */

argok:
	fildl	8(%esp)
	flds	4(%esp)
	fscale
	fstp	%st(1)

	/* Check for overflow and underflow */
	subl	$4, %esp
	fstps	(%esp)
	flds	(%esp)
	addl	$4, %esp
	fxam
	fnstsw	%ax
	andb	$0x45, %ah		/* Get the C3, C2 and C0 bits */
	cmpb	$0x05, %ah		/* infinity */
	je	RangeError
	cmpb	$0x40, %ah		/* zero */
	je	RangeError

	ret

zeroinfnan:				/* zero, inf or NaN */
	flds	4(%esp)
	ret

RangeError:
	movl	$2, _errno
	ret
