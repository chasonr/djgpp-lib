/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
	.text
	.globl	___modfl
___modfl:
	movl	16(%esp), %edx

	movl	12(%esp), %eax
	movl	%eax, 8(%edx)
	andl	$0x00007FFF, %eax
	cmpl	$0x00007FFF, %eax
	je	abarg			/* x is inf or NaN */

	subl	$0x3FFF, %eax		/* exponent as signed integer */
	jc	smallarg		/* |x| < 1 */

	cmpl	$63, %eax
	jge	bigarg

	cmpl	$32, %eax
	jge	loword

	/* radix point is in the high word */
	movl	%eax, %ecx
	movl	$0x80000000, %eax
	sarl	%cl, %eax		/* bit mask to form integer part */
	andl	8(%esp), %eax
	movl	%eax, 4(%edx)
	movl	$0, (%edx)
	jmp	makefraction

	/* radix point is in the low word */
loword:
	subl	$32, %eax
	movl	%eax, %ecx
	movl	$0x80000000, %eax
	sarl	%cl, %eax		/* bit mask to form integer part */
	andl	4(%esp), %eax
	movl	%eax, (%edx)
	movl	8(%esp), %eax
	movl	%eax, 4(%edx)

	/* subtract to make the fraction */
makefraction:
	fldt	4(%esp)
	fldt	(%edx)
	fsubrp
	ret

	/* |x| < 1 */
smallarg:
	fldt	4(%esp)
	movl	12(%esp), %eax
	andl	$0x00008000, %eax	/* a zero with the correct sign */
	movl	%eax, 8(%edx)
	movl	$0, 4(%edx)
	movl	$0, (%edx)
	ret

	/* |x| possibly infinity or possibly NaN */
abarg:
	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	orl	4(%esp), %eax
	jnz	isnan

	/* |x| too big to have a fraction; includes infinity */
bigarg:
	movl	4(%esp), %eax
	movl	%eax, (%edx)
	movl	8(%esp), %eax
	movl	%eax, 4(%edx)
	movl	12(%esp), %eax
	andl	$0x00008000, %eax	/* a zero with the correct sign */
	movl	%eax, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	fldt	4(%esp)
	ret

	/* NaNs return both as the fraction and as the integer */
isnan:
	fldt	4(%esp)
	fld	%st
	fstpt	(%edx)
	ret
