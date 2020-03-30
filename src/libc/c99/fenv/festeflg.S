/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* int fesetexceptflag(const fexcept_t *flagp, int excepts); */

    .globl _fesetexceptflag
_fesetexceptflag:
    mov 8(%esp), %eax   /* excepts -> EAX */
    cmp $0x3F, %eax
    ja L_return_error   /* unknown bits are set */

    /* Set the x87 exception flags */
    mov 4(%esp), %ecx   /* flagp -> ECX */
    mov (%ecx), %ecx    /* saved flags -> ECX */
    sub $28, %esp
    fstenv (%esp)       /* save the status word */
    mov 4(%esp), %edx   /* current flags -> EDX */
    xor %edx, %ecx      /* set new flags */
    and %eax, %ecx
    xor %edx, %ecx
    mov %ecx, 4(%esp)   /* load status word with new flags */
    fldenv (%esp)
    add $28, %esp

    /* Set the SSE exception flags */
    testl $0x02000000, __sse
    jz L_return_ok
    mov 8(%esp), %eax   /* excepts -> EAX */
    mov 4(%esp), %ecx   /* flagp -> ECX */
    mov 4(%ecx), %edx   /* current flags -> EDX */
    and %eax, %edx      /* use only the flags requested */
    sub $4, %esp
    stmxcsr (%esp)      /* push MXCSR */
    not %eax
    and %eax, (%esp)    /* modify MXCSR on stack */
    or %edx, (%esp)
    ldmxcsr (%esp)
    add $4, %esp

L_return_ok:
    xor %eax, %eax      /* return 0 */
    ret

L_return_error:
    xor %eax, %eax
    not %eax            /* return -1 */
    ret
