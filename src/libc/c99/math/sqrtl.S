/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_sqrtl
_sqrtl:
	movl	12(%esp), %eax		/* Test for infinity or NaN */
	andl	$0x00007FFF, %eax
	cmpl	$0x00007FFF, %eax
	je	abarg

argok:
	fldt	4(%esp)
	fsqrt

	/* Errors are indicated by a NaN result where the input was not a NaN */
	fxam
	fnstsw	%ax
	andb	$0x45, %ah
	cmpb	$0x01, %ah
	je	badarg

	ret

abarg:					/* infinity or NaN */
	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	orl	4(%esp), %eax
	jz	argok			/* infinity */

nanarg:
	fldt	4(%esp)
	ret

badarg:					/* x is definitely <0 */
	movl	$1, _errno
	ret
