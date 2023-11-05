/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.text

	.globl	_ilogb
_ilogb:

	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	jz	maybezero		/* x may be zero */
	cmpl	$0x7FF00000, %eax
	jge	abarg			/* x is infinity or NaN */

argok:
	fldl	4(%esp)
	fxtract
	fstp	%st
	subl	$4, %esp
	fistpl	(%esp)
	pop	%eax
	ret

maybezero:
	movl	4(%esp), %eax
	testl	%eax, %eax
	jnz	argok			/* x is subnormal */

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
