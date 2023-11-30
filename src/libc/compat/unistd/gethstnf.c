/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
__gethostname_chk(char *buf, int size, size_t bufsize)
{
    if (bufsize != (size_t)(-1) && size >= 0 && (unsigned)size > bufsize) {
        fputs("gethostname called with buffer size too small\n", stderr);
        abort();
    }

    return gethostname(buf, size);
}
