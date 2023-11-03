/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

.text
	.globl	_truncl
_truncl:
	subl	$4, %esp

	movl	16(%esp), %eax
	andl	$0x00007FFF, %eax
	cmpl	$0x00007FFF, %eax
	je	abarg

argok:
	fnstcw	(%esp)
	fwait
	movw	(%esp),%ax
	orw	$0x0c00, %ax
	movw	%ax, 2(%esp)
	fldcw	2(%esp)

	fldt	8(%esp)
	frndint

	fldcw	(%esp)

cleanup:
	addl	$4, %esp
	ret

abarg:					/* arg is infinity or NaN */
	fldt	8(%esp)
	jmp	cleanup
