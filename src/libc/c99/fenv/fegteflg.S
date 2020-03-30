/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* int fegetexceptflag(fexcept_t *flagp, int excepts); */

    .globl _fegetexceptflag
_fegetexceptflag:
    mov 8(%esp), %eax   /* excepts -> EAX */
    cmp $0x3F, %eax
    ja L_return_error   /* unknown bits are set */

    /* Save x87 flags */
    mov 4(%esp), %ecx   /* flagp -> ECX */
    fstsw (%ecx)        /* save exceptions */
    and %eax, (%ecx)

    /* Save SSE flags */
    testl $0x02000000, __sse
    jz L_return_ok
    stmxcsr 4(%ecx)

L_return_ok:
    xor %eax, %eax      /* return 0 */
    ret

L_return_error:
    xor %eax, %eax
    not %eax            /* return -1 */
    ret
