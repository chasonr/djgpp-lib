/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>
#include <libc/unconst.h>

wchar_t *
wcspbrk(const wchar_t *s1, const wchar_t *s2)
{
  const wchar_t *scanp;
  int c, sc;

  while ((c = *s1++) != 0)
  {
    for (scanp = s2; (sc = *scanp++) != 0;)
      if (sc == c)
	return unconst(s1 - 1, wchar_t *);
  }
  return 0;
}
