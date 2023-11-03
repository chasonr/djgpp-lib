/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
	.data
NaN:
	.long	0xFFC00000

	.text

	.globl	_remainderf
_remainderf:
	movl	4(%esp), %edx
	andl	$0x7FFFFFFF, %edx
	cmpl	$0x7F800000, %edx
	ja	argok			/* x is NaN */
	je	abx   			/* x is inf */

	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	je	badarg			/* y is zero */

argok:
	flds	8(%esp)
	flds	4(%esp)
	fprem1
	ret

abx:
	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7F800000, %eax
	jg	argok			/* y is NaN */

badarg:
	movl	$1, _errno
	jmp	argok			/* raise any exceptions */
