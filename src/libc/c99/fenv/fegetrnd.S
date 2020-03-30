/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* int fegetround(void); */

    .globl _fegetround
_fegetround:
    sub $4, %esp
    fstcw (%esp)
    pop %eax            /* control word -> EAX */
    shr $10, %eax       /* extract rounding bits */
    and $0x3, %eax
    ret
