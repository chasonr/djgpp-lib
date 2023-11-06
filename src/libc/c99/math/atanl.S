/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_atanl
_atanl:
	movl	12(%esp), %eax
	andl	$0x00007FFF, %eax
	cmpl	$0x00007FFF, %eax
	je	abarg

argok:
	fldt	4(%esp)
	fld1
	fpatan
	ret

abarg:
	movl	8(%esp), %eax		/* inf or NaN */
	andl	$0x7FFFFFFF, %eax	/* ignore the unused significand bit */
	orl	4(%esp), %eax
	jz	argok

badarg:					/* arg is NaN */
	fldt	4(%esp)
	ret
