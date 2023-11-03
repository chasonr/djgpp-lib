/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.text
	.globl	_modff			/* fract = fmod(x, &integer) */
_modff:
	movl	8(%esp), %edx

	movl	4(%esp), %eax		/* Check for NaN */
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7F800000, %eax
	jg	isnan

	shrl	$23, %eax
	subl	$0x7F, %eax		/* exponent as signed integer */
	jc	smallarg		/* |x| < 1 */

	cmpl	$23, %eax
	jge	bigarg

	movl	%eax, %ecx
	movl	$0xFF800000, %eax
	sarl	%cl, %eax		/* bit mask to form integer part */
	andl	4(%esp), %eax
	movl	%eax, (%edx)		/* store integer part */

	flds	4(%esp)
	fsubs	(%edx)
	ret

	/* |x| < 1 */
smallarg:
	flds	4(%esp)
	movl	4(%esp), %eax
	andl	$0x80000000, %eax	/* a zero with the correct sign */
	movl	%eax, (%edx)
	ret

	/* |x| too big to have a fraction; includes infinity */
bigarg:
	movl	4(%esp), %eax
	movl	%eax, (%edx)
	andl	$0x80000000, %eax	/* a zero with the correct sign */
	movl	%eax, 4(%esp)
	flds	4(%esp)
	ret

	/* NaNs return both as the fraction and as the integer */
isnan:
	flds	4(%esp)
	fsts	(%edx)
	ret
