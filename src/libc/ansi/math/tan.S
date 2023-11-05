/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_tan
_tan:
	movl	8(%esp), %eax

	andl	$0x7FFFFFFF, %eax
	cmpl	$0x43E00000, %eax	/* |x| >= 2^63 */
	jge	bigarg

	fldl	4(%esp)
	fptan
	fstp	%st(0)			/* Get rid of 1. */
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
					/* x is finite, but so huge the x87
					   can't compute result. tan(x) is
					   so ill-conditioned here that
					   result is meaningless anyway. */
	fldz				/* Return 0. by default. */
	ret
infinite:
	/* Intentionally raise the "invalid" exception */
	movl	$1, _errno
	fld1
	fchs
	fsqrt
	ret
