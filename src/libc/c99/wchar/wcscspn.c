/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>

size_t
wcscspn(const wchar_t *s1, const wchar_t *s2)
{
  const wchar_t *p, *spanp;
  wchar_t c, sc;

  for (p = s1;;)
  {
    c = *p++;
    spanp = s2;
    do {
      if ((sc = *spanp++) == c)
	return p - 1 - s1;
    } while (sc != 0);
  }
  /* NOTREACHED */
}
