/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* int feraiseexcept(int excepts); */

    .globl _feraiseexcept
_feraiseexcept:
    mov 4(%esp), %eax   /* excepts -> EAX */
    cmp $0x3F, %eax
    ja L_return_error   /* unknown bits are set */
    sub $28, %esp
    fstenv (%esp)       /* save exception flags */
    or %eax, 4(%esp)    /* set the bits */
    fldenv (%esp)       /* reload exception flags */
    add $28, %esp
    fwait               /* try to raise the exceptions */
    xor %eax, %eax      /* return 0 */
    ret
L_return_error:
    xor %eax, %eax
    not %eax            /* return -1 */
    ret
