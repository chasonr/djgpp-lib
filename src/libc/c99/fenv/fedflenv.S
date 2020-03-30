/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

.text
.globl ___dj_fe_dfl_env
___dj_fe_dfl_env:
    .word 0x0000033F /* __x87control: round to nearest, 64 bit precision, mask exceptions */
    .word 0x00000000 /* __x87flags: no exceptions pending */
    .word 0x00001F80 /* __ssecontrol: round to nearest, mask exceptions, IEEE compatible, no exceptions pending */
