/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
NaN:
	.long	0xFFC00000

	.globl	_sinl
_sinl:
	movl	12(%esp), %eax

	andl	$0x00007FFF, %eax
	cmpl	$0x0000403E, %eax	/* |x| >= 2^63 */
	jae	bigarg

	fldt	4(%esp)
	fsin
	ret

bigarg:
	cmpl	$0x00007FFF, %eax	/* x is INF or NaN. */
	jb	finite
	flds	NaN			/* Result is undefined. */
	movl	$1, _errno
	ret
finite:
	fldz				/* All precision lost; set sin = 0. */
	ret
