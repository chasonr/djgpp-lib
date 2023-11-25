/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>
#include <libc/file.h>

int
vwprintf(const wchar_t *fmt, va_list ap)
{
  int len;

  len = _dowprnt(fmt, ap, stdout);
  return (ferror(stdout) ? WEOF : len);
}
