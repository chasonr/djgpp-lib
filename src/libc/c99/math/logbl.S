/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.globl	_logbl
_logbl:
	fldt	4(%esp)
	fxtract
	fstp	%st
	ret
