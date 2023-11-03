/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

.text
	.globl	_truncf
_truncf:
	subl	$4, %esp

	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7F800000, %eax
	ja	abarg

argok:
	fnstcw	(%esp)
	fwait
	movw	(%esp),%ax
	orw	$0x0c00, %ax
	movw	%ax, 2(%esp)
	fldcw	2(%esp)

	flds	8(%esp)
	frndint

	fldcw	(%esp)

cleanup:
	addl	$4, %esp
	ret

abarg:					/* arg is infinity or NaN */
	flds	8(%esp)
	jmp	cleanup
