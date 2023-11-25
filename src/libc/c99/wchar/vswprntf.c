/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2004 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <errno.h>
#include <libc/file.h>

int
vswprintf(wchar_t *str, size_t n, const wchar_t *fmt, va_list ap)
{
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

  len = _dowprnt(fmt, ap, &_strbuf);

  /* Ensure nul termination */
  if (n > 0)
    *(wchar_t *)_strbuf._ptr = L'\0';

  return (0 <= len && (unsigned)len < n) ? len : -1;
}
