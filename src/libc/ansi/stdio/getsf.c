/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdio.h>
#include <stdlib.h>
#include <libc/file.h>

char *
__gets_chk(char *s, size_t ssize)
{
  int c;
  char *cs;
  char *s_end = s + ssize;

  if (ssize == 0) {
    fputs("gets called with zero-size buffer\n", stderr);
    abort();
  }

  stdin->_flag |= _IOBYTE;
  cs = s;
  while ((c = getchar()) != '\n' && c != EOF) {
    *cs++ = c;
    if (cs >= s_end) {
      fputs("gets buffer overrun\n", stderr);
      abort();
    }
  }
  if (c == EOF && cs==s)
    return NULL;
  *cs++ = '\0';
  return s;
}
