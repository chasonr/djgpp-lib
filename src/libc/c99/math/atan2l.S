/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2009 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
NaN:
	.long	0xFFC00000

	.globl	_atan2l
_atan2l:
	movl	12(%esp), %eax
	andl	$0x00007FFF, %eax
	cmpl	$0x00007FFF, %eax
	je	aby			/* y is inf or NaN */

	movl	24(%esp), %edx
	andl	$0x00007FFF, %edx
	cmpl	$0x00007FFF, %edx
	je	abx

argok:
	fldt	4(%esp)
	fldt	16(%esp)
	fpatan
	ret

aby:
	movl	8(%esp), %eax		/* inf or NaN */
	andl	$0x7FFFFFFF, %eax	/* Ignore unused significand bit */
	orl	4(%esp), %eax
	jz	argok			/* y = inf */
	jmp	badarg

abx:
	movl	20(%esp), %eax		/* inf or NaN */
	andl	$0x7FFFFFFF, %eax	/* Ignore unused significand bit */
	orl	16(%esp), %eax
	jz	argok			/* y = inf */

badarg:					/* arg is NaN */
	movl	$1, _errno
	flds	NaN
	ret
