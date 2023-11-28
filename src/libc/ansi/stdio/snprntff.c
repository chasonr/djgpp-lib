/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int
__snprintf_chk(char * restrict str, size_t n, int flag, size_t strsize, const char * restrict format, ...)
{
  va_list argp;
  size_t lesser_size = (strsize < n) ? strsize : n;

  va_start(argp, format);
  int rc = __vsnprintf_chk(str, lesser_size, flag, strsize, format, argp);
  va_end(argp);
  if (strsize != (size_t)(-1) && strsize > n && rc >= 0
  &&  (size_t)rc >= strsize) {
    fputs("snprintf buffer overrun\n", stderr);
    abort();
  }

  return rc;
}
