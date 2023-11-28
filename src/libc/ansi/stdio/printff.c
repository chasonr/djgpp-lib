/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdarg.h>
#include <stdio.h>

int
__printf_chk(int flag, const char * restrict format, ...)
{
  va_list argp;

  va_start(argp, format);
  int rc = __vfprintf_chk(stdout, flag, format, argp);
  va_end(argp);

  return rc;
}
