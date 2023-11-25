/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2007 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <libc/file.h>

int
fwprintf(register FILE *iop, const wchar_t *fmt, ...)
{
  va_list args;
  int len;
  char localbuf[BUFSIZ];

  va_start(args, fmt);

  if (iop->_flag & _IONBF)
  {
    iop->_flag &= ~_IONBF;
    iop->_ptr = iop->_base = localbuf;
    iop->_bufsiz = BUFSIZ;
    len = _dowprnt(fmt, args, iop);
    fflush(iop);
    iop->_flag |= _IONBF;
    iop->_base = NULL;
    iop->_bufsiz = 0;
    iop->_cnt = 0;
  }
  else
    len = _dowprnt(fmt, args, iop);

  va_end(args);

  return ferror(iop) ? WEOF : len;
}
