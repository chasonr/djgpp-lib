/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
	.file "wmemcpy.s"
	.text
	.balign	16,,7
	.globl	_wmemcpy
_wmemcpy:
	pushl	%ebp
	movl	%esp,%ebp
	pushl	%esi
	pushl	%edi
	movl	8(%ebp),%edi
	movl	12(%ebp),%esi
	movl	16(%ebp),%ecx
	shl	    $1,%ecx
	call	___dj_movedata
	popl	%edi
	popl	%esi
	movl	8(%ebp),%eax
	leave
	ret

