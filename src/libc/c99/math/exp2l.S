/* Copyright (C) 2011 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */

pinf:
	.long	0x7F800000

	.globl	_exp2l
_exp2l:
	movl	12(%esp), %eax		/* Test for special cases. */
	movl	%eax, %edx
	andl	$0x00007FFF, %eax
	cmpl	$0x00007FFF, %eax
	je	abarg
	andl	$0x0000FFFF, %edx
	xorl	$0x00008000, %edx
	cmpl	$0x0000C00D, %edx
	jge	bigarg			/* normal args: */
					/* 0 < |x| <= log2(LDBL_MAX) */
argok:					/* log2(LDBL_MAX) = 0x400D0000000000000000 */
	fldt	4(%esp)
	fld	%st			/* xs	    xs		  */
	frndint				/* nint(xs) xs		  */
	fxch	%st(1)			/* xs	    nint(xs)	  */
	fsub	%st(1), %st		/* fract    nint	  */
	f2xm1				/* exps()-1 nint	  */
	fld1				/* 1	    exps-1   nint */
	faddp				/* exps	    nint	  */
	fscale				/* exp	    nint	  */
	fstp	%st(1)			/* exp			  */
	ret

bigarg:
	movl	$2, _errno		/* |x| is really big, but finite */
	jmp	argok

abarg:					/* x = +/-inf, or +NaN */
	movl	8(%esp), %eax
	andl	$0x7FFFFFFF, %eax	/* Ignore the unused significand bit */
	orl	4(%esp), %eax
	jnz	badarg

infarg:					/* |x| = inf */
	testl	$0x00008000, 12(%esp)
	jz	posinf

neginf:
	fldz
	ret

posinf:
	flds	pinf
	ret

badarg:					/* arg is NaN */
	fldt	4(%esp)
	ret
