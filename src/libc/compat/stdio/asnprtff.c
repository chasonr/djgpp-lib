/* Copyright (C) 2014 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2008 DJ Delorie, see COPYING.DJ for details */
#define __DJ_CHECKED_FUNCTION
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

char *
__asnprintf_chk(char * restrict str, size_t * restrict np, int flag, size_t strsize, const char * restrict fmt, ...)
{
  va_list args;
  char *buffer;

  if (str != NULL && strsize != (size_t)(-1) && strsize < *np) {
    fputs("asnprintf called with buffer size too small\n", stderr);
    abort();
  }

  va_start(args, fmt);
  buffer = __vasnprintf_chk(str, np, flag, strsize, fmt, args);
  va_end(args);

  return buffer;
}
