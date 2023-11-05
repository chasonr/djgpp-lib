/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
	.data
NaN:
	.long	0xFFC00000

	.text

	.globl	_fmod
_fmod:
	movl	8(%esp), %edx
	andl	$0x7FFFFFFF, %edx	/* x exponent */

	movl	16(%esp), %eax
	andl	$0x7FF00000, %eax	/* y exponent */
	je	zeroy

	cmpl	$0x7FF00000, %edx
	je	abx			/* x is inf or NaN */

argok:
	fldl	12(%esp)
	fldl	4(%esp)
	fprem
	fstp	%st(1)
	ret

abx:					/* x is inf or NaN */
	movl	4(%esp), %edx
	testl	%edx, %edx
	jnz	argok			/* x is NaN */

	/* x is infinite; check for y NaN */
	cmp	$0x7FF00000, %eax
	jb	badarg			/* y is finite */
	jg	argok			/* y is NaN */
	movl	12(%esp), %eax
	testl	%eax, %eax
	jnz	argok			/* y is NaN */
	jmp	badarg			/* y is not NaN */

zeroy:					/* y is zero or subnormal */
	movl	12(%esp), %eax
	testl	%eax, %eax
	jnz	argok			/* y is submormal */

	/* y is zero; check for x NaN */
	cmp	$0x7FF00000, %edx
	jb	badarg			/* x is finite */
	jg	argok			/* x is NaN */
	movl	4(%esp), %edx
	testl	%eax, %eax
	jnz	argok			/* x is NaN */

badarg:					/* arg is NaN */
	movl	$1, _errno
	jmp	argok			/* raise any exceptions */
