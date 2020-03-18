/* Copyright (C) 2005 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <libc/stubs.h>
#include <wchar.h>

/* wcstok is analogous, not to strtok, but to POSIX strtok_r */
wchar_t *
wcstok(wchar_t *s, const wchar_t *delim, wchar_t **last)
{
  const wchar_t *spanp;
  int c, sc;
  wchar_t *tok;

  if (s == NULL && (s = *last) == NULL)
    return (NULL);

  /*
   * Skip (span) leading delimiters (s += wcsspn(s, delim), sort of).
   */
 cont:
  c = *s++;
  for (spanp = delim; (sc = *spanp++) != 0;) {
    if (c == sc)
      goto cont;
  }

  if (c == 0) {			/* no non-delimiter characters */
    *last = NULL;
    return (NULL);
  }
  tok = s - 1;

  /*
   * Scan token (scan for delimiters: s += wcscspn(s, delim), sort of).
   * Note that delim must have one NUL; we stop if we see that, too.
   */
  for (;;) {
    c = *s++;
    spanp = delim;
    do {
      if ((sc = *spanp++) == c) {
	if (c == 0)
	  s = NULL;
	else
	  s[-1] = 0;
	*last = s;
	return (tok);
      }
    } while (sc != 0);
  }
  /* NOTREACHED */
}
