/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* int fetestexcept(int excepts); */

    .globl _fetestexcept
_fetestexcept:
    /* Get x87 exception flags */
    mov 4(%esp), %eax   /* excepts -> EAX */
    sub $4, %esp
    fstsw (%esp)        /* save exception flags */
    and (%esp), %eax    /* return flags & excepts */
    add $4, %esp

    /* Get SSE exception flags */
    testl $0x02000000, __sse
    jz L_return_ok
    sub $4, %esp
    stmxcsr (%esp)
    pop %edx
    and 4(%esp), %edx
    or %edx, %eax

L_return_ok:
    and $0x3F, %eax     /* mask unknown bits */
    ret
