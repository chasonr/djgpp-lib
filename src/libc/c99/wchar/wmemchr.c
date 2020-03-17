/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>
#include <libc/unconst.h>

wchar_t *
wmemchr(const wchar_t *s, wchar_t c, size_t n)
{
  if (n)
  {
    const wchar_t *p = s;
    char cc = c;
    do {
      if (*p == cc)
        return unconst(p, wchar_t *);
      p++;
    } while (--n != 0);
  }
  return 0;
}
