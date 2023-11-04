/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.data
three:	.long 3

	.text

	.globl _cbrtl
_cbrtl:

	movl	12(%esp), %eax
	movl	%eax, %ecx		/* Save sign */

	andl	$0x00007FFF, %eax
	je	verysmall
	cmpl	$0x00007FFF, %eax
	je	zero_inf_nan		/* x is infinite or a NaN */

argok:
	fld1
	fldt	4(%esp)
	fabs
	fyl2x				/* log2(x) */
	fildl	three
	fdivrp				/* l3 = log2(x)/3 */
	fld	%st			/* l3 l3 */
	frndint				/* int(l3) l3 */
	fxch				/* l3 int(l3) */
	fsub	%st(1)			/* frac(l3) int(l3) */
	f2xm1				/* 2**frac(l3)-1 int(l3) */
	fld1				/* 1 2**frac(l3)-1 int(l3) */
	faddp				/* 2**frac(l3) int(l3) */
	fscale				/* 2**l3 int(l3) */
	fstp	%st(1)			/* 2**l3 */

	/* Include the sign */
	test	$0x8000, %ecx
	jz	1f
	    fchs
	1:

	ret

verysmall:
	mov	8(%esp), %eax
	or	4(%esp), %eax
	jne	argok			/* Process denormal through argok */
	/* arg is zero: return it */
zero_inf_nan:
	fldt	4(%esp)
	ret
