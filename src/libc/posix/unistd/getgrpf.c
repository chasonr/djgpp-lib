/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
__getgroups_chk(int gidsetsize, gid_t *grouplist, size_t grouplistsize)
{
    if (grouplistsize != (size_t)(-1) && gidsetsize >= 0 && grouplistsize < (unsigned)gidsetsize) {
        fputs("getgroups called with buffer size too small\n", stderr);
        abort();
    }

    return getgroups(gidsetsize, grouplist);
}
