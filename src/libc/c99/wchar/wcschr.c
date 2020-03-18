/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>
#include <libc/unconst.h>

wchar_t *
wcschr(const wchar_t *s, wchar_t c)
{
  wchar_t cc = c;
  while (*s)
  {
    if (*s == cc)
      return unconst(s, wchar_t *);
    s++;
  }
  if (cc == 0)
    return unconst(s, wchar_t *);
  return 0;
}

