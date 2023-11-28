/* Copyright (C) 2008 DJ Delorie, see COPYING.DJ for details */
#define __DJ_CHECKED_FUNCTION
#include <stdarg.h>
#include <stdio.h>

int
__asprintf_chk(char ** restrict strp, int flag, const char * restrict fmt, ...)
{
  va_list args;
  int len;

  va_start(args, fmt);
  len = __vasprintf_chk(strp, flag, fmt, args);
  va_end(args);

  return len;
}
