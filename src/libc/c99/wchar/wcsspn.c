/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>

size_t
wcsspn(const wchar_t *s1, const wchar_t *s2)
{
  const wchar_t *p = s1, *spanp;
  wchar_t c, sc;

 cont:
  c = *p++;
  for (spanp = s2; (sc = *spanp++) != 0;)
    if (sc == c)
      goto cont;
  return (p - 1 - s1);
}
