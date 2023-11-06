/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

ninf:
	.long	0xFF800000

pinf:
	.long	0x7F800000

.text
	.globl	_log1p
_log1p:					/* ln(1.+x) */
					/* log1p(x) */
	/* NaNs and positive infinities should propagate quietly */
	movl	8(%esp), %eax
	cmpl	$0xFFF00000, %eax
	jae	maybenan		/* negative infinity or NaN */
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7FF00000, %eax
	jae	infnan			/* positive infinity or NaN */

argok:
	cmpl	$0x3FD2BEC3, %eax	/* 1 - sqrt(0.5) */
	fldln2				/* ln(2) */
	jbe	logp1
	fld1
	faddl	4(%esp)
	fyl2x				/* logi(x) */

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
logp1:					/* log1pi(x) */
	fldl	4(%esp)
	fyl2xp1
	ret

maybenan:
	andl	$0x7FFFFFFF, %eax
	movl	4(%esp), %edx
	testl	%edx, %edx
	jz	argok			/* Raise exception on negative infinity */

infnan:
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
