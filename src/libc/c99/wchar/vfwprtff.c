/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>
#include <libc/file.h>

int
__vfwprintf_chk(FILE * restrict f, int flag, const wchar_t * restrict fmt, va_list ap)
{
  int len;
  char localbuf[BUFSIZ];

  if (f->_flag & _IONBF)
  {
    f->_flag &= ~_IONBF;
    f->_ptr = f->_base = localbuf;
    f->_bufsiz = BUFSIZ;
    len = __dowprnt_chk(fmt, ap, f, flag);
    (void)fflush(f);
    f->_flag |= _IONBF;
    f->_base = NULL;
    f->_bufsiz = 0;
    f->_cnt = 0;
  }
  else
    len = __dowprnt_chk(fmt, ap, f, flag);
  return (ferror(f) ? WEOF : len);
}
