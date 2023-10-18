/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
NaN:
	.long	0xFFC00000

	.globl	_atanf
_atanf:
	movl	4(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x7F800000, %eax
	ja	badarg

argok:
	flds	4(%esp)
	fld1
	fpatan
	ret

badarg:					/* arg is NaN */
	movl	$1, _errno
	flds	NaN
	ret
