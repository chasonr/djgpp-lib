/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>
#include <libc/unconst.h>

wchar_t *
wcsrchr(const wchar_t *s, wchar_t c)
{
  wchar_t cc = c;
  const wchar_t *sp=(wchar_t *)0;
  while (*s)
  {
    if (*s == cc)
      sp = s;
    s++;
  }
  if (cc == 0)
    sp = s;
  return unconst(sp, wchar_t *);
}

