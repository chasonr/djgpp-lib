/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *
__getcwd_chk(char *buf, size_t size, size_t bufsize)
{
    if (bufsize != (size_t)(-1) && bufsize < size) {
        fputs("getcwd called with buffer size too small\n", stderr);
        abort();
    }

    return getcwd(buf, size);
}
