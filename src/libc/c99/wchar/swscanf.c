/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2004 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <stdarg.h>
#include <libc/file.h>

int
swscanf(const wchar_t *str, const wchar_t *fmt, ...)
{
  int r;
  va_list a=0;
  FILE _strbuf;

  va_start(a, fmt);
  __stropenwr(&_strbuf, str);
  r = _dowscan(&_strbuf, fmt, a);
  va_end(a);
  return r;
}
