/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>

int
wmemcmp(const wchar_t *s1, const wchar_t *s2, size_t n)
{
  if (n != 0)
  {
    const wchar_t *p1 = s1, *p2 = s2;

    do {
      if (*p1++ != *p2++)
        return (*--p1 - *--p2);
    } while (--n != 0);
  }
  return 0;
}
