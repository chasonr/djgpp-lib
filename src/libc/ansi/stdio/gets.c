/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <libc/file.h>

char *
gets(char *s)
{
  int c;
  char *cs;

  stdin->_flag |= _IOBYTE;
  cs = s;
  while ((c = getchar()) != '\n' && c != EOF)
    *cs++ = c;
  if (c == EOF && cs==s)
    return NULL;
  *cs++ = '\0';
  return s;
}
