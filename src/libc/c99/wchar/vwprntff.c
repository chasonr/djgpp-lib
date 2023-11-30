/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <wchar.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int
__vwprintf_chk(int flag, const wchar_t * restrict format, va_list arg)
{
  return __vfwprintf_chk(stdout, flag, format, arg);
}
