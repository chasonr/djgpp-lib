/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

ssize_t
__read_chk(int fildes, void *buf, size_t nbyte, size_t bufsize)
{
    if (bufsize != (size_t)(-1) && bufsize < nbyte) {
        fputs("read called with buffer size too small\n", stderr);
        abort();
    }

    return read(fildes, buf, nbyte);
}
