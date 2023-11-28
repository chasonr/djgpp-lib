/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdarg.h>
#include <stdio.h>

int
__vprintf_chk(int flag, const char * restrict format, va_list ap)
{
  return __vfprintf_chk(stdout, flag, format, ap);
}
