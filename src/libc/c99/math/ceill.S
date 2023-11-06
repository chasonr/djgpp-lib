/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

.text
	.globl	_ceill
_ceill:
	subl	$4, %esp

	movl	16(%esp), %eax
	andl	$0x00007FFF, %eax
	cmpl	$0x00007FFF, %eax
	je	abarg

argok:
	fnstcw	(%esp)
	fwait
	movw	(%esp),%ax
	andw	$0xf3ff, %ax
	orw	$0x0800, %ax
	movw	%ax, 2(%esp)
	fldcw	2(%esp)

	fldt	8(%esp)
	frndint

	fldcw	(%esp)

cleanup:
	addl	$4, %esp
	ret

abarg:
	movl	12(%esp), %eax		/* inf or NaN */
	andl	$0x7FFFFFFF, %eax	/* ignore the unused significand bit */
	orl	8(%esp), %eax
	jz	argok

badarg:					/* arg is NaN */
	fldt	8(%esp)
	jmp	cleanup
