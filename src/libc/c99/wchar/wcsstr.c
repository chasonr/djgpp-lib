/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>
#include <libc/unconst.h>

wchar_t *
wcsstr(const wchar_t *s, const wchar_t *find)
{
  wchar_t c, sc;
  size_t len;

  if ((c = *find++) != 0)
  {
    len = wcslen(find);
    do {
      do {
	if ((sc = *s++) == 0)
	  return 0;
      } while (sc != c);
    } while (wcsncmp(s, find, len) != 0);
    s--;
  }
  return unconst(s, wchar_t *);
}
