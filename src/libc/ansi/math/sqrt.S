/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_sqrt
_sqrt:
	movl	8(%esp), %eax		/* Test for NaN */
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7FF00000, %eax
	jg	nanarg			/* x is NaN */
	je	abarg			/* x is infinity or NaN */

argok:
	fldl	4(%esp)
	fsqrt

	/* Errors are indicated by a NaN result where the input was not a NaN */
	fxam
	fnstsw	%ax
	andb	$0x45, %ah
	cmpb	$0x01, %ah
	je	badarg

	ret

abarg:					/* infinity or NaN */
	movl	4(%esp), %eax
	testl	%eax, %eax
	jz	argok			/* infinity */

nanarg:
	fldl	4(%esp)
	ret

badarg:	
	movl	$1, _errno
	ret
