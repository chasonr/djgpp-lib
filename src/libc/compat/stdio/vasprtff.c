/* Copyright (C) 2008 DJ Delorie, see COPYING.DJ for details */
#define __DJ_CHECKED_FUNCTION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libc/file.h>

int
__vasprintf_chk(char ** restrict strp, int flag, const char * restrict fmt, va_list argsp)
{
  FILE _strbuf;
  int len;


  /*  Just query how much space is needed.  */
  memset(&_strbuf, 0, sizeof(_strbuf));
  __stropenw(&_strbuf, NULL, 0);
  len = __doprnt_chk(fmt, argsp, &_strbuf, flag);

  *strp = NULL;
  if (len != EOF)
  {
    *strp = malloc(len + 1);
    if (*strp)
    {
      __stropenw(&_strbuf, *strp, len);
      len = __doprnt_chk(fmt, argsp, &_strbuf, flag);
      __strclosew(&_strbuf);
      if (len == EOF)
      {
        free(*strp);
        *strp = NULL;
      }
    }
    else
      len = EOF;
  }

  return len;
}
