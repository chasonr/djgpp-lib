/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2009 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
NaN:
	.long	0xFFC00000

	.globl	_atan2
_atan2:
	movl	8(%esp), %eax
	andl	$0x7FF00000, %eax
	cmpl	$0x7FF00000, %eax
	je	aby			/* y is inf or NaN */

	movl	16(%esp), %edx
	andl	$0x7FF00000, %edx
	cmpl	$0x7FF00000, %edx
	je	abx

argok:
	fldl	4(%esp)
	fldl	12(%esp)
	fpatan
	ret

aby:
	movl	8(%esp), %eax		/* inf or NaN */
	testl	$0x000FFFFF, %eax
	jne	badarg			/* y = NaN */
	movl	4(%esp), %eax
	testl	%eax, %eax
	jz	argok
	jmp	badarg

abx:
	movl	16(%esp), %eax		/* inf or NaN */
	testl	$0x000FFFFF, %eax
	jne	badarg			/* x = NaN */
	movl	12(%esp), %eax
	testl	%eax, %eax
	jz	argok

badarg:					/* arg is NaN */
	movl	$1, _errno
	flds	NaN
	ret
