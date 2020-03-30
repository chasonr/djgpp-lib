/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* int fegetenv(fenv_t *envp); */

    .globl _fegetenv
_fegetenv:
    mov 4(%esp), %edx   /* envp -> EDX */

    /* Save x87 state */
    sub $28, %esp
    fstenv (%esp)
    mov (%esp), %eax    /* control word */
    mov %eax, (%edx)
    mov 4(%esp), %eax   /* status word */
    mov %eax, 4(%edx)
    fldenv (%esp)       /* preserve exception enable flags */
    add $28, %esp

    /* Save SSE state */
    testl $0x02000000, __sse
    jz L_return_ok
    stmxcsr 8(%edx)

L_return_ok:
    xor %eax, %eax      /* return 0 */
    ret
