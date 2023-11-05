/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_cosl
_cosl:
	movl	12(%esp), %eax

	andl	$0x00007FFF, %eax
	cmpl	$0x0000403E, %eax	/* |x| >= 2^63 */
	jge	bigarg

	fldt	4(%esp)
	fcos
	ret

bigarg:
	cmpl	$0x00007FFF, %eax	/* x is INF or NaN. */
	jne	finite
abarg:
	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	orl	4(%esp), %eax
	je	infinite
	fldt	4(%esp)			/* Propagate NaN */
	ret
finite:
	fld1				/* cos = 1. */
	ret
infinite:
	/* Intentionally raise the "invalid" exception */
	movl	$1, _errno
	fld1
	fchs
	fsqrt
	ret
