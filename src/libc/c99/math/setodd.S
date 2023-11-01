/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

        .globl  ___dj_set_odd

// Set the least significant bit of a long double
// fmaf, fma and fmal all use this for stages of rounding other than the last
___dj_set_odd:
        orb     $1, 4(%esp)
        fldt    4(%esp)
        ret
