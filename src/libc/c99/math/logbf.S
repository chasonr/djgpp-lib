/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.globl	_logbf
_logbf:
	flds	4(%esp)
	fxtract
	fstp	%st
	ret
