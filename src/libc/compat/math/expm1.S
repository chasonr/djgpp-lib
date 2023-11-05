/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_expm1
_expm1:
	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax
	cmpl	$0x3FE00000, %eax
	jge	bigarg

	/* In range for f2xm1 */
smallarg:
	fldl	4(%esp)
	fldl2e				/* log2(e)  x			   */
	fmulp				/* xs				   */
	f2xm1				/* exps-1       		   */
	ret

bigarg:
	/* Punt these to exp */
	push	8(%esp)
	push	8(%esp)
	call	_exp
	addl	$8, %esp
	fld1
	fsubrp
	ret
