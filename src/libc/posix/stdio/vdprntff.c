/* Copyright (C) 2014 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */
#define __DJ_CHECKED_FUNCTION
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
__vdprintf_chk(int fd, int flag, const char * restrict fmt, va_list ap)
{
  char *string;
  int written;


  written = __vasprintf_chk(&string, flag, fmt, ap);
  if (string)
  {
    written = write(fd, string, written);
    free(string);
  }

  return written;
}
