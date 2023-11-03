/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.globl	_rint
_rint:
	fldl	4(%esp)
	frndint
	ret
