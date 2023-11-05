/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_expm1f
_expm1f:
	movl	4(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x3F000000, %eax
	jge	bigarg

	/* In range for f2xm1 */
smallarg:
	flds	4(%esp)
	fldl2e				/* log2(e)  x			   */
	fmulp				/* xs				   */
	f2xm1				/* exps-1       		   */
	ret

bigarg:
	/* Punt these to expf */
	push	4(%esp)
	call	_expf
	addl	$4, %esp
	fld1
	fsubrp
	ret
