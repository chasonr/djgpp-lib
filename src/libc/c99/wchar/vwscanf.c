/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>

int
vwscanf(const wchar_t *fmt, va_list ap)
{
  return _dowscan(stdin, fmt, ap);
}
