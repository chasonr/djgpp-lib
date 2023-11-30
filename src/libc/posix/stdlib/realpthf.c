/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *
__realpath_chk(const char *path, char *resolved, size_t resolvedlen)
{
    if (resolved != NULL && resolvedlen != (size_t)(-1)) {
        char *buf = realpath(path, NULL);
        if (buf == NULL) {
            return NULL;
        }
        if (strlen(buf) >= resolvedlen) {
            fputs("realpath buffer overrun\n", stderr);
            abort();
        }
        strcpy(resolved, buf);
        free(buf);
        return resolved;
    } else {
        return realpath(path, resolved);
    }
}
