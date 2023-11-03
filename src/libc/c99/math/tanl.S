/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
NaN:
	.long	0xFFC00000

	.globl	_tanl
_tanl:
	movl	12(%esp), %eax
	andl	$0x00007FFF, %eax
	cmpl	$0x0000403E, %eax	/* |x| >= 2^63 */
	jae	abarg

	fldt	4(%esp)
	fptan
	fstp	%st(0)			/* Get rid of 1. */
	ret

abarg:
	cmpl	$0x00007FFF, %eax
	je	badarg
					/* x is finite, but so huge the x87
					   can't compute result. tan(x) is
					   so ill-conditioned here that
					   result is meaningless anyway. */
	fldz				/* Return 0. by default. */
	ret	

badarg:					/* x = inf or NaN */
	movl	$1, _errno
	flds	NaN
	ret
