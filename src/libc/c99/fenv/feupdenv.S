/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* int feupdateenv(const fenv_t *envp); */

    .globl _feupdateenv
_feupdateenv:
    mov 4(%esp), %edx   /* envp -> EDX */

    /* Load x87 state */
    sub $28, %esp
    fstenv (%esp)
    mov (%edx), %eax    /* control word */
    mov %eax, (%esp)
    mov 4(%edx), %ecx   /* status word */
    mov 4(%esp), %eax
    and $0xBF, %cl      /* merge bits 7 and 5-0 only */
    or %cl, %al
    mov %eax, 4(%esp)
    fldenv (%esp)       /* update exception flags */
    add $28, %esp

    /* Load SSE state */
    testl $0x02000000, __sse
    jz L_return_ok
    sub $4, %esp
    stmxcsr (%esp)
    pop %eax            /* MXCSR -> EAX */
    and $0x3F, %eax     /* keep any pending exceptions */
    or 8(%edx), %eax    /* merge pending exceptions and reload floating point settings */
    push %eax
    ldmxcsr (%esp)      /* EAX -> MXCSR */
    add $4, %esp

L_return_ok:
    fwait               /* raise exceptions */
    xor %eax, %eax      /* return 0 */
    ret
