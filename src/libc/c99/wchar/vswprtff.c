/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2004 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <libc/file.h>

int
__vswprintf_chk(wchar_t * restrict str, size_t n, int flag, size_t ssize, const wchar_t * restrict fmt, va_list ap)
{
  /* vswprintf returns -1 instead of actual size if the buffer is too short.
     Just bail if ssize < n */
  if (ssize != (size_t)(-1) && ssize < n) {
    fputs("vswprintf called with buffer size too small\n", stderr);
    abort();
  }

  FILE _strbuf;
  int len;

  /* _cnt is an int in the FILE structure. To prevent wrap-around, we limit
   * n to between 0 and INT_MAX inclusively. */
  if (n > INT_MAX)
  {
    errno = EFBIG;
    return -1;
  }

  memset(&_strbuf, 0, sizeof(_strbuf));

  /* If n == 0, just querying how much space is needed. */
  if (n > 0)
    __stropenw(&_strbuf, (char *)str, (n - 1) * sizeof(wchar_t));
  else
    __stropenw(&_strbuf, NULL, 0);

  len = __dowprnt_chk(fmt, ap, &_strbuf, flag);

  /* Ensure nul termination */
  if (n > 0)
    *(wchar_t *)_strbuf._ptr = L'\0';

  return (0 <= len && (unsigned)len < n) ? len : -1;
}
