/* Copyright (C) 2014 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */
#define __DJ_CHECKED_FUNCTION
#include <stdio.h>
#include <stdarg.h>

int
__dprintf_chk(int fd, int flag, const char * restrict fmt, ...)
{
  va_list arg_list;
  int written;


  va_start(arg_list, fmt);
  written = __vdprintf_chk(fd, flag, fmt, arg_list);
  va_end(arg_list);

  return written;
}
