/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.text

	.globl	_ilogbf
_ilogbf:

	movl	4(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	jz	zero			/* x is zero */
	cmpl	$0x7F800000, %eax
	jge	abarg			/* x is infinity or NaN */

argok:
	flds	4(%esp)
	fxtract
	fstp	%st
	subl	$4, %esp
	fistpl	(%esp)
	pop	%eax
	ret

zero:
	movl	$1, _errno
	movl	$0x80000001, %eax	/* FP_ILOGB0 */
	jmp	invalid

abarg:
	movl	$1, _errno
	movl	$0x7FFFFFFF, %eax

	/* Raise the "invalid" exception */
invalid:
	fld1
	fchs
	fsqrt
	fstp	%st
	ret
