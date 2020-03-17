/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
	.file "wmemset.s"
	.text
	.balign	16,,7
	.globl	_wmemset
_wmemset:
	pushl	%ebp
	movl	%esp,%ebp
	pushl	%edi
	movl	8(%ebp),%edi
	movl	12(%ebp),%eax
	movl	16(%ebp),%ecx
	cld

	# We will handle wmemsets of <= 15 bytes one character at a time.
	# This avoids some extra overhead for small wmemsets, and
	# knowing we are setting > 15 bytes eliminates some annoying
	# checks in the "long move" case.
	cmpl	$15,%ecx
	jle	L3

	# Otherwise, tile the word value out into %eax.
	# 0x20AC -> 0x20AC20AC, etc.
	movl	%eax,%edx
	sall	$16,%eax
	movw	%dx,%ax
	jmp	L2

	# Handle any cruft necessary to get %edi long-aligned.
L1:	stosw
	decl	%ecx
L2:	testl	$2,%edi
	jnz	L1

	# Now slam out all of the longs.
	movl	%ecx,%edx
	shrl	$1,%ecx
	rep
	stosl

	# Finally, handle any trailing cruft.  We know the high three bytes
	# of %ecx must be zero, so just put the "slop count" in the low byte.
	movb	%dl,%cl
	andb	$1,%cl
L3:	rep
	stosw
	popl	%edi
	movl	8(%ebp),%eax
	leave
	ret
