/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_sqrtf
_sqrtf:
	movl	4(%esp), %eax		/* Test for NaN */
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7F800000, %eax
	jg	nanarg

argok:
	flds	4(%esp)
	fsqrt

	/* Errors are indicated by a NaN result where the input was not a NaN */
	fxam
	fnstsw	%ax
	andb	$0x45, %ah
	cmpb	$0x01, %ah
	je	badarg

	ret

nanarg:
	flds	4(%esp)
	ret

badarg:					/* x is definitely <0 */
	movl	$1, _errno
	ret
