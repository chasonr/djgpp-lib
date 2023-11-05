/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_sin
_sin:
	movl	8(%esp), %eax

	andl	$0x7FFFFFFF, %eax
	cmpl	$0x43E00000, %eax	/* |x| >= 2^63 */
	jge	bigarg

	fldl	4(%esp)
	fsin
	ret

bigarg:
	cmpl	$0x7FF00000, %eax	/* x is INF or NaN. */
	jl	finite
	jg	nanarg
	movl	4(%esp), %eax
	testl	%eax, %eax
	je	infinite
nanarg:
	fldl	4(%esp)			/* Propagate NaN */
	ret
finite:
	fldz				/* All precision lost; set sin = 0. */
	ret
infinite:
	/* Intentionally raise the "invalid" exception */
	movl	$1, _errno
	fld1
	fchs
	fsqrt
	ret
