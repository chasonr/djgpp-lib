/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.globl	_rintl
_rintl:
	fldt	4(%esp)
	frndint
	ret
