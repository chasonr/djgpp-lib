/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.globl	_rintf
_rintf:
	flds	4(%esp)
	frndint
	ret
