/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.globl	_logf
_logf:
	/* NaNs and positive infinities should propagate quietly */
	movl	4(%esp), %eax
	cmpl	$0x7F800000, %eax
	je	infnan			/* positive infinity */
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7F800000, %eax
	jg	infnan			/* NaN */

	/* Compute the log; let any exceptions occur */
	fldln2
	flds	4(%esp)
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

	/* Propagate NaN or positive infinity quietly */
infnan:
	flds	4(%esp)
	ret

	/* Domain error */
edom:
	movl	$1, _errno
	ret

	/* Range error */
erange:
	movl	$2, _errno
	ret
