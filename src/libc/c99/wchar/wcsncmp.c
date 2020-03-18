/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>

static int
transform(wchar_t ch)
{
  if (ch >= 0xE000)
    return ch - 0x0800; /* E000..FFFF => D800..F7FF */
  if (ch >= 0xD800)
    return ch + 0x2000; /* D800..DFFF => F800..FFFF */
  return ch;            /* 0000..D7FF => 0000..D7FF */
}

int
wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t n)
{

  if (n == 0)
    return 0;
  do {
    if (*s1 != *s2++)
      return transform(*s1) - transform(*--s2);
    if (*s1++ == 0)
      break;
  } while (--n != 0);
  return 0;
}
