/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.text

	.globl	_copysign
_copysign:

	movl	8(%esp), %eax
	movl	16(%esp), %edx
	xor	%edx, %eax
	and	$0x7FFFFFFF, %eax
	xor	%edx, %eax
	movl	%eax, 8(%esp)
	fldl	4(%esp)
	ret
