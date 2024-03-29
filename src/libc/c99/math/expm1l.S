/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_expm1l
_expm1l:
	movl	12(%esp), %eax
	andl	$0x00007FFF, %eax
	cmpl	$0x00003FFE, %eax
	jge	bigarg

	/* In range for f2xm1 */
smallarg:
	fldt	4(%esp)
	fldl2e				/* log2(e)  x			   */
	fmulp				/* xs				   */
	f2xm1				/* exps-1       		   */
	ret

bigarg:
	/* Punt these to expl */
	push	12(%esp)
	push	12(%esp)
	push	12(%esp)
	call	_expl
	addl	$12, %esp
	fld1
	fsubrp
	ret
