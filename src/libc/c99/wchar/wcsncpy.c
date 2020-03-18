/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>

wchar_t *
wcsncpy(wchar_t *dst, const wchar_t *src, size_t n)
{
  if (n != 0) {
    wchar_t *d = dst;
    const wchar_t *s = src;

    do {
      if ((*d++ = *s++) == 0)
      {
	while (--n != 0)
	  *d++ = 0;
	break;
      }
    } while (--n != 0);
  }
  return dst;
}
