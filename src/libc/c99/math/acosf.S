/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_acosf
_acosf:
/*	The commonly-used formula

	acos(x) = atan2(sqrt(1.-x*x), x)

	is a bad way to compute the arc cosine, since there are errors for
	x near 1 (or -1) caused by inaccuracies in forming x*x.	 However, the
	argument to the square root can be computed accurately even for x near 1
	by the alternate form

	acos(x) = atan2(sqrt((1.+x)*(1.-x)), x)

	which is used here.
	*/

	movl	4(%esp), %eax		/* is x >= 1? */
	andl	$0x7FFFFFFF, %eax	/* |x| */
	cmpl	$0x7F800000, %eax
	jg	nanarg

argok:
	flds	4(%esp)			/* x		  */
	fld	%st(0)			/* x	x	  */
	fld	%st(0)			/* x	x   x	  */
	fld1				/* 1	x   x	x */
	faddp	%st, %st(2)		/* x	1+x x	  */
	fld1				/* 1	x   1+x	  */
	/* Should be fsubrp %st, %st(1) (gas bug) */
	.byte	0xDE, 0xE1		/* 1-x	1+x x	  */
	fmulp				/* 1-x2 x	  */
	fsqrt
	fxch
	fpatan

	/* Check for NaN return */
	fxam
	fnstsw	%ax
	andb	$0x45, %ah
	cmpb	$0x01, %ah		/* NaN */
	je	badarg

	ret

badarg:
	movl	$1, _errno
	ret

nanarg:
	flds	4(%esp)
	ret
