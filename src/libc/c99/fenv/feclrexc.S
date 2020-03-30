/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* int feclearexcept(int excepts); */

    .globl _feclearexcept
_feclearexcept:
    mov 4(%esp), %eax   /* excepts -> EAX */
    cmp $0x3F, %eax
    ja L_return_error   /* unknown bits are set */

    /* clear the x87 exceptions */
    sub $28, %esp
    fstenv (%esp)       /* save exception flags */
    not %eax
    and %eax, 4(%esp)   /* clear the bits */
    fldenv (%esp)       /* reload exception flags */
    add $28, %esp

    /* clear the SSE exceptions */
    testl $0x02000000, __sse
    jz L_return_ok
    mov 4(%esp), %eax
    not %eax
    sub $4, %esp
    stmxcsr (%esp)
    and %eax, (%esp)
    ldmxcsr (%esp)
    add $4, %esp

L_return_ok:
    xor %eax, %eax      /* return 0 */
    ret

L_return_error:
    xor %eax, %eax
    not %eax            /* return -1 */
    ret
