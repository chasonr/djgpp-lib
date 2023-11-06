/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

infinity:
	.long	0x7F800000

	.globl	_hypotf
_hypotf:
	/* Check for non-finite values */
	/* hypotf(inf, nan) is supposed to return infinity, so check for
	   infinity first */
	movl	4(%esp), %eax
	and	$0x7FFFFFFF, %eax
	cmp	$0x7F800000, %eax
	je	isinfinite

	movl	8(%esp), %edx
	and	$0x7FFFFFFF, %edx
	cmp	$0x7F800000, %edx
	je	isinfinite

	jg	isnan_y
	cmp	$0x7F800000, %eax
	jg	isnan_x

	/* Both arguments are finite */

	flds	4(%esp)
	fmul	%st, %st
	flds	8(%esp)
	fmul	%st, %st
	faddp
	fsqrt

	/* Check for overflow and indicate range error */
	subl	$4, %esp
	fstps	(%esp)
	flds	(%esp)
	addl	$4, %esp
	fxam
	fnstsw	%ax
	andb	$0x45, %ah		/* Get the C3, C2 and C0 bits */
	cmpb	$0x05, %ah		/* infinity */
	je	RangeError

	ret

RangeError:
	movl	$2, _errno
	ret

isinfinite:
	flds	infinity
	ret

isnan_x:
	flds	4(%esp)
	ret

isnan_y:
	flds	8(%esp)
	ret
