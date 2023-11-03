/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.globl	_logl
_logl:
	/* NaNs and positive infinities should propagate quietly */
	movl	12(%esp), %eax
	cmpw	$0x7FFF, %ax
	je	infnan			/* positive infinity or NaN */
	cmpw	$0xFFFF, %ax
	je	maybenan		/* negative infinity or NaN */

	/* Compute the log; let any exceptions occur */
argok:
	fldln2
	fldt	4(%esp)
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

	/* Either a NaN or a negative infinity */
maybenan:
	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	orl	4(%esp), %eax
	jz	argok			/* negative infinity */

	/* Propagate NaN or positive infinity quietly */
infnan:
	fldt	4(%esp)
	ret

	/* Domain error */
edom:
	movl	$1, _errno
	ret

	/* Range error */
erange:
	movl	$2, _errno
	ret
