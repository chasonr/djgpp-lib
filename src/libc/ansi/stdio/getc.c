/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <libc/file.h>

int
getc(FILE *f)
{
  f->_flag |= _IOBYTE;
  return __getc(f);
}
