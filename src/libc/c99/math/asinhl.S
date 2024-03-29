/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

	.globl	_asinhl
_asinhl:
	/* long double asinhl(long double x) {
	The textbook formula

		asinh(x) = ln(x + sqrt(x*x + 1.))

	involves loss of precision for x small and x negative.	To avoid these
	problems, we split the range by computing

		asinh(x) = -asinh(-x)

	for negative x.	 The textbook formula still involves cancellation, but
	can be put in the form

		asinh(x) = log1p(x + x*x/(sqrt(x*x + 1.) + 1.))
	
	where log1p(x) = log(1+x), a built-in x87 coprocessor function.	 This
	form has no cancellation problems, since all the subexpressions are
	positive.
	*/

	movl	12(%esp), %eax
	movl	%eax, %ecx
	andl	$0x00007FFF, %eax
	cmpl	$0x00007FFF, %eax
	je	inf_nan
	cmpl	$0x00005FFE, %eax
	ja	alt_formula		/* Avoid overflow */


	fldln2				/* ln2			  */
	fldt	4(%esp)			/* x	 ln2		  */
	fabs				/* |x|	 ln2		  */
	fld	%st			/* x	 x    ln2	  */
	fmul	%st, %st		/* x*x	      x	  ln2	  */
	fld1				/* 1	 x*x  x	  ln2	  */
	fadd	%st(1), %st		/* 1+x*x x*x  x	  ln2	  */
	fsqrt				/* sqrt	 x*x  x	  ln2	  */
	fld1				/* 1	 sqrt x*x x   ln2 */
	faddp				/* den	 x*x  x	  ln2	  */
	/* Should be fdivp %st, %st(1) (gas bug) */
	.byte	0xDE, 0xF9		/* quo	 x    ln2	  */
	faddp				/* arg	 ln2		  */

	andl	$0x7FFFFFFF, %eax
	cmpl	$0x3FD6A09E, %eax
	jbe	1f
	fld1
	faddp
	fyl2x				/* logi(x) */
	jmp	2f
1:
		fyl2xp1			/* log1pi(x) */
2:
	testl	$0x8000, %ecx		/* test for sign bit */
	jz	3f
		fchs
3:
	ret

	/* Compute as log(x) + log(2) */
alt_formula:
	fldln2				/* ln2		     */
	fldt	4(%esp)			/* x	 ln2	     */
	fabs				/* |x|   ln2         */
	fyl2x				/* log(|x|)          */
	fldln2				/* ln2   log(|x|)    */
	faddp
	testl	$0x8000, %ecx
	jz	4f
		fchs
4:
	ret

inf_nan:
	fldt	4(%esp)			/* +/- inf: just load arg */
	ret
