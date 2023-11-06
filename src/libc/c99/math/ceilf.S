/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

.text
	.globl	_ceilf
_ceilf:
	subl	$4, %esp

	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7F800000, %eax
	ja	badarg

argok:
	fnstcw	(%esp)
	fwait
	movw	(%esp),%ax
	andw	$0xf3ff, %ax
	orw	$0x0800, %ax
	movw	%ax, 2(%esp)
	fldcw	2(%esp)

	flds	8(%esp)
	frndint

	fldcw	(%esp)

cleanup:
	addl	$4, %esp
	ret

badarg:					/* arg is NaN */
	flds	8(%esp)
	jmp	cleanup
