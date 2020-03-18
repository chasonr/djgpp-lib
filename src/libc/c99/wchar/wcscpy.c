/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>

wchar_t *
wcscpy(wchar_t *to, const wchar_t *from)
{
  wchar_t *save = to;

  for (; (*to = *from); ++from, ++to);
  return save;
}
