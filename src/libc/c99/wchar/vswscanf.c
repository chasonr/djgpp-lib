/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2004 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>
#include <libc/file.h>

int
vswscanf(const wchar_t *str, const wchar_t *fmt, va_list ap)
{
  FILE _strbuf;

  __stropenwr(&_strbuf, str);
  return _dowscan(&_strbuf, fmt, ap);
}
