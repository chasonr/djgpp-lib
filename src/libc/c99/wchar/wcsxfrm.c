/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>

size_t
wcsxfrm(dst, src, n)
     wchar_t *dst;
     const wchar_t *src;
     size_t n;
{
  size_t r = 0;
  wchar_t c;

  if (n != 0) {
    while ((c = *src++) != 0)
    {
      r++;
      if (--n == 0)
      {
        while (*src++ != 0)
          r++;
        break;
      }
      *dst++ = c;
    }
    *dst = 0;
  }
  return r;
}
