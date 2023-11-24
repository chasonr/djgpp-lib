/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <libc/file.h>

#undef putchar
int
putchar(int c)
{
  stdout->_flag |= _IOBYTE;
  return __putc(c, stdout);
}
