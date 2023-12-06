/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int
__vsprintf_chk(char * restrict s, int flag, size_t ssize, const char * restrict format, va_list ap)
{
  size_t snsize = (ssize > INT_MAX) ? INT_MAX : ssize;
  int rc = __vsnprintf_chk(s, snsize, flag, ssize, format, ap);
  if (ssize != (size_t)(-1) && rc >= 0 && (size_t)rc >= ssize) {
    fputs("vsprintf buffer overrun\n", stderr);
    abort();
  }

  return rc;
}
