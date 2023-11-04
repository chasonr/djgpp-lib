/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

	.data
three:	.long 3

	.text

	.globl _cbrtf
_cbrtf:

	movl	4(%esp), %eax
	movl	%eax, %ecx		/* Save sign */

	andl	$0x7FFFFFFF, %eax
	je	zero_inf_nan		/* Avoid log of zero */
	cmpl	$0x7F800000, %eax
	jge	zero_inf_nan		/* Propagate infinity and NaN */

	fld1
	flds	4(%esp)
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
	test	%ecx, %ecx
	jns	1f
	    fchs
	1:

	ret

zero_inf_nan:
	flds	4(%esp)
	ret
