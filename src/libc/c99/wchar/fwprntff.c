/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdarg.h>
#include <stdio.h>

int
__fwprintf_chk(FILE * restrict stream, int flag, const wchar_t * restrict format, ...)
{
  va_list argp;

  va_start(argp, format);
  int rc = __vfwprintf_chk(stream, flag, format, argp);
  va_end(argp);

  return rc;
}
