/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* int fesetround(int round); */

    .globl _fesetround
_fesetround:
    mov 4(%esp), %ecx   /* round -> ecx */
    cmp $3, %ecx
    ja  L_return_error  /* unknown rounding mode specified */

    /* Set x87 rounding mode */
    shl $10, %ecx       /* shift to the position in the control word */
    sub $4, %esp
    fstcw (%esp)
    pop %eax            /* control word -> EAX */
    and $~0x0C, %ah
    or  %ch, %ah        /* place rounding bits */
    push %eax           /* EAX -> control word */
    fldcw (%esp)
    add $4, %esp

    /* Set SSE rounding mode */
    testl $0x02000000, __sse
    jz L_return_ok
    shl $3, %ecx        /* place rounding bits */
    sub $4, %esp
    stmxcsr (%esp)
    pop %eax
    and $~0x60, %ah
    or %ch, %ah
    push %eax
    ldmxcsr (%esp)
    add $4, %esp

L_return_ok:
    xor %eax, %eax      /* return 0 */
    ret

L_return_error:
    xor %eax, %eax
    not %eax            /* return -1 */
    ret
