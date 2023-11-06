/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

inf:
	.long	0x7F800000

	.globl	_hypot
_hypot:
	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7FF00000, %eax
	ja	nanx
	je	abx			/* x = huge, INF or NaN */

	/* x is finite */
	movl	16(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7FF00000, %eax
	ja	return_y
	jae	aby			/* y = huge, INF or NaN */

argok:
	fldl	4(%esp)
	fmul	%st, %st
	fldl	12(%esp)
	fmul	%st, %st
	faddp
	fsqrt

	/* Check for overflow */
	subl	$8, %esp
	fstpl	(%esp)
	fldl	(%esp)
	addl	$8, %esp
	fxam
	fnstsw	%ax
	andb	$0x45, %ah
	cmpb	$0x05, %ah		/* infinity */
	je	range_error

	ret

range_error:
	movl	$2, _errno
	ret

abx:
	/* x may be infinity or NaN */
	movl	4(%esp), %eax
	testl	%eax, %eax
	je	infinity

nanx:
	/* x is a NaN.  Return x unless y is infinity. */
	movl	16(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7FF00000, %eax
	jne	return_x
	movl	12(%esp), %eax
	testl	%eax, %eax
	je	infinity

	/* x is a NaN and y is not infinity */
return_x:
	fldl	4(%esp)
	ret

aby:
	/* x is finite; y may be infinity or NaN */
	movl	12(%esp), %eax
	testl	%eax, %eax
	je	infinity

	/* x is finite and y is a NaN */
return_y:
	fldl	12(%esp)
	ret

infinity:
	flds	inf
	ret
