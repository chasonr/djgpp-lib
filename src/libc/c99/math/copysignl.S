/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.text

	.globl	_copysignl
_copysignl:

	movl	12(%esp), %eax
	movl	24(%esp), %edx
	xor	%edx, %eax
	and	$0xFFFF7FFF, %eax
	xor	%edx, %eax
	movl	%eax, 12(%esp)
	fldt	4(%esp)
	ret
