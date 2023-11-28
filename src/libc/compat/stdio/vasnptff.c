/* Copyright (C) 2014 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2008 DJ Delorie, see COPYING.DJ for details */
#define __DJ_CHECKED_FUNCTION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <errno.h>
#include <libc/file.h>

char *
__vasnprintf_chk(char * restrict str, size_t * restrict np, int flag, size_t strsize, const char * restrict fmt, va_list argsp)
{
  FILE _strbuf;
  char *buffer = str;
  int len = *np;

  if (str != NULL && strsize != (size_t)(-1) && strsize < *np) {
    fputs("vasnprintf called with buffer size too small\n", stderr);
    abort();
  }


  /*  _cnt is an int in the FILE structure. To prevent wrap-around,
   *  we limit n to between 0 and INT_MAX inclusively.  */
  if (len > INT_MAX)
  {
    errno = EFBIG;
    return NULL;
  }

  memset(&_strbuf, 0, sizeof(_strbuf));
  if (buffer && len > 0)
    len--;
  else
  {
    /*  Just query how much space is needed.  */
    __stropenw(&_strbuf, NULL, 0);
    len = __doprnt_chk(fmt, argsp, &_strbuf, flag);
    if (len == EOF)
      return NULL;
    buffer = malloc(len + 1);
    if (!buffer)
      return NULL;
  }

  __stropenw(&_strbuf, buffer, len);
  len = __doprnt_chk(fmt, argsp, &_strbuf, flag);
  if (len == EOF)
  {
    free(buffer);
    buffer = NULL;
  }
  else if (len > 0)
  {
    *np = len;
    __strclosew(&_strbuf);  /* Ensure nul termination */
  }

  return buffer;
}
