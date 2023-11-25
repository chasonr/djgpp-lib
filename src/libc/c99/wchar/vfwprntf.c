/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>
#include <libc/file.h>

int
vfwprintf(FILE *f, const wchar_t *fmt, va_list ap)
{
  int len;
  char localbuf[BUFSIZ];

  if (f->_flag & _IONBF)
  {
    f->_flag &= ~_IONBF;
    f->_ptr = f->_base = localbuf;
    f->_bufsiz = BUFSIZ;
    len = _dowprnt(fmt, ap, f);
    (void)fflush(f);
    f->_flag |= _IONBF;
    f->_base = NULL;
    f->_bufsiz = 0;
    f->_cnt = 0;
  }
  else
    len = _dowprnt(fmt, ap, f);
  return (ferror(f) ? WEOF : len);
}
