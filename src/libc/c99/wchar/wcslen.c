/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>

size_t
wcslen(const wchar_t *str)
{
  const wchar_t *s;

  for (s = str; *s; ++s);
  return s-str;
}

