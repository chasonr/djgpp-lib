/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
NaN:
	.long	0xFFC00000

pinf:
	.long	0x7F800000

	.globl	_expm1l
_expm1l:
	/* The algorithm used in expm1 and expm1f overflows prematurely
	   for expm1l. Use expl for large inputs to avoid the overflow. */

	movl	12(%esp), %eax
	andl	$0x00007FFF, %eax
	cmpl	$0x00003FFE, %eax
	jae	bigarg

	/* In range for f2xm1 */
smallarg:
	fldt	4(%esp)
	fldl2e				/* log2(e)  x			   */
	fmulp				/* xs				   */
	fld	%st			/* xs	    xs			   */
	f2xm1				/* exps-1   nint		   */
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
