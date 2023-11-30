/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int
__swprintf_chk(wchar_t * restrict str, size_t n, int flag, size_t strsize, const wchar_t * restrict format, ...)
{
  /* swprintf returns -1 instead of actual size if the buffer is too short.
     Just bail if strsize < n */
  if (strsize != (size_t)(-1) && strsize < n) {
    fputs("swprintf called with buffer size too small\n", stderr);
    abort();
  }

  va_list argp;

  va_start(argp, format);
  int rc = __vswprintf_chk(str, n, flag, strsize, format, argp);
  va_end(argp);

  return rc;
}
