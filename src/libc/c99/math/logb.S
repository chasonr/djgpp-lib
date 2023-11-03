/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.globl	_logb
_logb:
	fldl	4(%esp)
	fxtract
	fstp	%st
	ret
