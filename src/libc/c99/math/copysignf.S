/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.text

	.globl	_copysignf
_copysignf:

	movl	4(%esp), %eax
	movl	8(%esp), %edx
	xor	%edx, %eax
	and	$0x7FFFFFFF, %eax
	xor	%edx, %eax
	movl	%eax, 4(%esp)
	flds	4(%esp)
	ret
