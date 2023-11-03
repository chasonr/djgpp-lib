/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

.text
	.globl	_trunc
_trunc:
	subl	$4, %esp

	movl	12(%esp), %eax
	andl	$0x7FF00000, %eax
	cmpl	$0x7FF00000, %eax
	je	abarg

argok:
	fnstcw	(%esp)
	fwait
	movw	(%esp),%ax
	orw	$0x0c00, %ax
	movw	%ax, 2(%esp)
	fldcw	2(%esp)

	fldl	8(%esp)
	frndint

	fldcw	(%esp)

cleanup:
	addl	$4, %esp
	ret

abarg:					/* arg is infinity or NaN */
	fldl	8(%esp)
	jmp	cleanup
