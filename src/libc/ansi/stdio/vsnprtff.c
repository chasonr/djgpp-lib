/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2004 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
#define __DJ_CHECKED_FUNCTION
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <libc/file.h>

int
__vsnprintf_chk(char * restrict str, size_t n, int flag, size_t strsize, const char * restrict fmt, va_list ap)
{
  FILE _strbuf;
  int len;
  size_t lesser_size = (strsize < n) ? strsize : n;

  if (strsize == 0 && str != NULL) {
    fputs("vsnprintf called with empty output buffer\n", stderr);
    return -1;
  }

  /* _cnt is an int in the FILE structure. To prevent wrap-around, we limit
   * n to between 0 and INT_MAX inclusively. */
  if (n > INT_MAX)
  {
    errno = EFBIG;
    return -1;
  }

  memset(&_strbuf, 0, sizeof(_strbuf));

  /* If lesser_size == 0, just querying how much space is needed. */
  if (lesser_size > 0)
    __stropenw(&_strbuf, str, lesser_size - 1);
  else
    __stropenw(&_strbuf, NULL, 0);

  len = __doprnt_chk(fmt, ap, &_strbuf, flag);

  /* Ensure nul termination */
  if (lesser_size > 0)
    __strclosew(&_strbuf);

  if (strsize != (size_t)(-1) && strsize > n && len >= 0
  &&  (size_t)len >= strsize) {
    fputs("vsnprintf buffer overrun\n", stderr);
    abort();
  }

  return len;
}
