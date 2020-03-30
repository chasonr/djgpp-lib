/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* int fesetenv(const fenv_t *envp); */

    .globl _fesetenv
_fesetenv:
    mov 4(%esp), %edx   /* envp -> EDX */

    /* Load x87 state */
    sub $28, %esp
    fstenv (%esp)
    mov (%edx), %eax    /* control word */
    mov %eax, (%esp)
    mov 4(%edx), %ecx   /* status word */
    mov 4(%esp), %eax
    and $0xBF, %cl      /* restore bits 7 and 5-0 only */
    and $0x40, %al
    or %cl, %al
    mov %eax, 4(%esp)
    fldenv (%esp)       /* update exception flags */
    add $28, %esp

    /* Load SSE state */
    testl $0x02000000, __sse
    jz L_return_ok
    ldmxcsr 8(%edx)

L_return_ok:
    xor %eax, %eax      /* return 0 */
    ret
