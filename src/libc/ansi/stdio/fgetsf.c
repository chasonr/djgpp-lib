/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdio.h>
#include <stdlib.h>

char *
__fgets_chk(char * restrict s, int n, FILE * restrict f, size_t ssize)
{
  if (ssize != (size_t)(-1) && n >= 0 && (size_t)n > ssize) {
    fputs("fgets called with buffer size too small\n", stderr);
    abort();
  }

  return fgets(s, n, f);
}
