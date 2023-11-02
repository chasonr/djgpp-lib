/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.text

	.globl	_ilogbl
_ilogbl:

	movl	12(%esp), %eax
	andl	$0x00007FFF, %eax
	jz	maybezero		/* x may be zero */
	cmpl	$0x00007FFF, %eax
	je	abarg			/* x is infiinity or NaN */

argok:
	fldt	4(%esp)
	fxtract
	fstp	%st
	subl	$4, %esp
	fistpl	(%esp)
	pop	%eax
	ret

maybezero:
	movl	4(%esp), %eax
	orl	8(%esp), %eax
	jnz	argok			/* x is subnormal */

	movl	$1, _errno
	movl	$0x80000001, %eax	/* FP_ILOGB0 */
	ret

abarg:
	movl	$1, _errno
	movl	$0x7FFFFFFF, %eax
	ret
