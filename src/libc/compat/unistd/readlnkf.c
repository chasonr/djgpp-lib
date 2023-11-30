/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
__readlink_chk(const char * file, char * buffer, size_t size, size_t buffersize)
{
    if (buffersize != (size_t)(-1) && (unsigned)size > buffersize) {
        fputs("readlink called with buffer size too small\n", stderr);
        abort();
    }

    return readlink(file, buffer, size);
}
