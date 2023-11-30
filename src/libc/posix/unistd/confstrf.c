/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

size_t
__confstr_chk(int name, char *buf, size_t len, size_t bufsize)
{
    if (bufsize != (size_t)(-1) && bufsize < len) {
        fputs("confstr called with buffer size too small\n", stderr);
        abort();
    }

    return confstr(name, buf, len);
}
