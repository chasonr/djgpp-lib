/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>
#include <libc/file.h>

int
wscanf(const wchar_t *fmt, ...)
{
  int r;
  va_list a=0;
  va_start(a, fmt);
  r = _dowscan(stdin, fmt, a);
  va_end(a);
  return r;
}
