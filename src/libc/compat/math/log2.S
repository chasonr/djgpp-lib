/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_log2
_log2:
	movl	8(%esp), %eax		/* Test for abnormal arg. */
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7FF00000, %eax
	ja	nanarg
	je	abarg

argok:					/* Proceed with normal log calc. */
	fld1
	fldl	4(%esp)
	fyl2x

	/* Check for errors */
	/* log never overflows but may return negative infinity */
	fxam
	fnstsw	%ax
	andb	$0x45, %ah
	cmpb	$0x01, %ah		/* NaN */
	je	edom
	cmpb	$0x05, %ah		/* infinity */
	je	erange

	ret

abarg:
	movl	4(%esp), %eax
	testl	%eax, %eax
	jnz	nanarg			/* NaN */

	movl	8(%esp), %eax
	cmpl	$0xFFF00000, %eax
	jz	argok			/* -inf; raise the exception */

	/* Propagate NaNs */
nanarg:
	fldl	4(%esp)
	ret

	/* Domain error */
edom:
	movl	$1, _errno
	ret

	/* Range error */
erange:
	movl	$2, _errno
	ret
