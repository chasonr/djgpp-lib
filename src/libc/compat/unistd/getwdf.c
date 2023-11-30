/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

char *
__getwd_chk(char *buffer, size_t buffersize)
{
    char *rc;

    if (buffersize != (size_t)(-1)) {
        rc = getcwd(buffer, buffersize);
        if (rc == NULL && errno == ERANGE) {
            fputs("getwd buffer overrun\n", stderr);
            abort();
        }
    } else {
        rc = getwd(buffer);
    }
    return rc;
}
