/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* int feholdexcept(fenv_t *envp); */

    .globl _feholdexcept
_feholdexcept:
    mov 4(%esp), %edx   /* envp -> EDX */

    /* Set up x87 state */
    sub $28, %esp
    fstenv (%esp)
    mov (%esp), %eax    /* control word */
    mov %eax, (%edx)
    or $0x3F, %eax      /* disable all exceptions */
    mov %eax, (%esp)
    mov 4(%esp), %eax   /* status word */
    mov %eax, 4(%edx)
    and $~0x3F, %eax    /* clear all exceptions */
    mov %eax, 4(%esp)
    fldenv (%esp)       /* update exception flags */
    add $28, %esp

    /* Set up SSE state */
    testl $0x02000000, __sse
    jz L_return_ok
    stmxcsr 8(%edx)
    mov 8(%edx), %eax
    and $0xFFFFFFC0, %eax
    or  $0x00001F80, %eax
    push %eax
    ldmxcsr (%esp)
    add $4, %esp

L_return_ok:
    xor %eax, %eax      /* return 0 */
    ret
