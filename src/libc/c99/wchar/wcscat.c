/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>

wchar_t *
wcscat(wchar_t *s, const wchar_t *append)
{
  wchar_t *save = s;

  for (; *s; ++s);
  while ((*s++ = *append++));
  return save;
}
