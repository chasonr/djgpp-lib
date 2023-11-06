/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.text

	.globl	_remainderl
_remainderl:

	movl	12(%esp), %edx
	andl	$0x00007FFF, %edx	/* x exponent */

	movl	24(%esp), %eax
	andl	$0x00007FFF, %eax	/* y exponent */
	je	zeroy			/* y is subnormal or zero */

	cmpl	$0x00007FFF, %edx
	je	abx			/* x is inf or NaN */

	/* x is zero, subnormal or normal; y is normal, infinite or NaN */

argok:
	fldt	16(%esp)
	fldt	4(%esp)
	fprem1
	fstp	%st(1)
	ret

abx:					/* x is inf or NaN */
	movl	8(%esp), %edx
	andl	$0x7FFFFFFF, %edx	/* Ignore the unused significand bit */
	orl	4(%esp), %edx
	jnz	argok			/* x is NaN */

	/* x is infinite; check for y NaN */
	cmp	$0x00007FFF, %eax
	jne	badarg			/* y is finite */
	movl	20(%esp), %eax
	andl	$0x7FFFFFFF, %eax	/* Ignore the unused significand bit */
	orl	16(%esp), %eax
	jnz	argok			/* y is NaN */
	jmp	badarg			/* y is not NaN */

zeroy:					/* y is zero or subnormal */
	movl	20(%esp), %eax
	andl	$0x7FFFFFFF, %eax	/* Ignore the unused significand bit */
	orl	16(%esp), %eax
	jnz	argok			/* y is subnormal */

	/* y is zero; check for x NaN */
	cmp	$0x00007FFF, %edx
	jne	badarg			/* x is finite */
	movl	8(%esp), %edx
	andl	$0x7FFFFFFF, %edx	/* Ignore the unused significand bit */
	orl	4(%esp), %edx
	jnz	argok			/* x is NaN */

badarg:
	movl	$1, _errno
	jmp	argok			/* raise any exceptions */
