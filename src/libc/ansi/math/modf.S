/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.text
	.globl	_modf			/* fract = fmod(x, &integer) */
_modf:
	movl	12(%esp), %edx

	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7FF00000, %eax
	jg	isnan
	je	abarg			/* x is inf or NaN */

	shrl	$20, %eax
	subl	$0x3FF, %eax		/* exponent as signed integer */
	jc	smallarg		/* |x| < 1 */

	cmpl	$52, %eax
	jge	bigarg

	cmpl	$21, %eax
	jge	loword

	/* radix point is in the high word */
	movl	%eax, %ecx
	movl	$0xFFF00000, %eax
	sarl	%cl, %eax		/* bit mask to form integer part */
	andl	8(%esp), %eax
	movl	%eax, 4(%edx)
	movl	$0, (%edx)
	jmp	makefraction

	/* radix point is in the low word */
loword:
	subl	$21, %eax
	movl	%eax, %ecx
	movl	$0x80000000, %eax
	sarl	%cl, %eax		/* bit mask to form integer part */
	andl	4(%esp), %eax
	movl	%eax, (%edx)
	movl	8(%esp), %eax
	movl	%eax, 4(%edx)

	/* subtract to make the fraction */
makefraction:
	fldl	4(%esp)
	fsubl	(%edx)
	ret

	/* |x| < 1 */
smallarg:
	fldl	4(%esp)
	movl	8(%esp), %eax
	andl	$0x80000000, %eax	/* a zero with the correct sign */
	movl	%eax, 4(%edx)
	movl	$0, (%edx)
	ret

	/* |x| possibly infinity or possibly NaN */
abarg:
	movl	4(%esp), %eax
	testl	%eax, %eax
	jnz	isnan

	/* |x| too big to have a fraction; includes infinity */
bigarg:
	movl	4(%esp), %eax
	movl	%eax, (%edx)
	movl	8(%esp), %eax
	movl	%eax, 4(%edx)
	andl	$0x80000000, %eax	/* a zero with the correct sign */
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	fldl	4(%esp)
	ret

	/* NaNs return both as the fraction and as the integer */
isnan:
	fldl	4(%esp)
	fstl	(%edx)
	ret
