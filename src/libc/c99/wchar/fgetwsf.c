/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

wchar_t *
__fgetws_chk(wchar_t * restrict s, int n, FILE * restrict stream, size_t ssize)
{
  if (ssize != (size_t)(-1) && n >= 0 && (size_t)n > ssize) {
    fputs("fgets called with buffer size too small\n", stderr);
    abort();
  }

  return fgetws(s, n, stream);
}
