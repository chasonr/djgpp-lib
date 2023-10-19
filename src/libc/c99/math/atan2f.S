/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2009 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
NaN:
	.long	0xFFC00000

	.globl	_atan2f
_atan2f:
	movl	4(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7F800000, %eax
	ja	badarg			/* y is NaN */

	movl	8(%esp), %edx
	andl	$0x7FFFFFFF, %edx
	cmpl	$0x7F800000, %edx
	ja	badarg

argok:
	flds	4(%esp)
	flds	8(%esp)
	fpatan
	ret

badarg:					/* arg is NaN */
	movl	$1, _errno
	flds	NaN
	ret
