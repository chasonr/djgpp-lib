/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
NaN:
	.long	0xFFC00000

	.globl	_cosf
_cosf:
	movl	4(%esp), %eax

	andl	$0x7FFFFFFF, %eax
	cmpl	$0x5F000000, %eax	/* |x| >= 2^63 */
	jae	bigarg

	flds	4(%esp)
	fcos
	ret

bigarg:
	cmpl	$0x7F800000, %eax	/* x is INF or NaN. */
	jb	finite
	flds	NaN			/* Result is undefined. */
	movl	$1, _errno
	ret
finite:
	fld1				/* cos = 1. */
	ret
