/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdlib.h>
#include <wchar.h>

int
mblen(const char *s, size_t n)
{
  unsigned char ch;
  wint_t wc;
  if (s)
  {
    if (n == 0)
      return -1;
    ch = (unsigned char)*s;
    if (ch == 0)
      return 0;
    wc = btowc(ch);
    if (wc == WEOF)
      return -1;
    return 1;
  }
  else
    return 0;
}
