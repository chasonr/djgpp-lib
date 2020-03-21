/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <limits.h>
#include <wctype.h>
#include <errno.h>
#include <wchar.h>
#include <libc/unconst.h>

long long int
wcstoll(const wchar_t *nptr, wchar_t **endptr, int base)
{
  const wchar_t *s = (const wchar_t *) nptr;
  unsigned long long int acc;
  wchar_t c;
  unsigned long long int cutoff;
  int neg = 0, any, cutlim;

  /*
   * See wcstol for comments as to the logic used.
   */
  do {
    c = *s++;
  } while (iswspace(c));
  if (c == L'-')
  {
    neg = 1;
    c = *s++;
  }
  else if (c == L'+')
    c = *s++;
  if ((base == 0 || base == 16) &&
      c == L'0' && (*s == L'x' || *s == L'X'))
  {
    c = s[1];
    s += 2;
    base = 16;
  }
  if (base == 0)
    base = c == L'0' ? 8 : 10;

/* to prevent overflow, we take max-1 and add 1 after division */
  cutoff = neg ? -(LLONG_MIN+1) : LLONG_MAX-1;
  cutlim = cutoff % base;
  cutoff /= base;
  if (++cutlim == base)
  {
    cutlim = 0;
    cutoff++;
  }
  for (acc = 0, any = 0; ; c = *s++)
  {
    if (iswdigit(c))
      c -= L'0';
    else if (iswalpha(c))
      c -= iswupper(c) ? L'A' - 10 : L'a' - 10;
    else
      break;
    if (c >= base)
      break;
    if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
      any = -1;
    else
    {
      any = 1;
      acc *= base;
      acc += c;
    }
  }
  if (any < 0)
  {
    acc = neg ? LLONG_MIN : LLONG_MAX;
    errno = ERANGE;
  }
  else if (neg)
    acc = -acc;
  if (endptr != 0)
    *endptr = any ? unconst(s, wchar_t *) - 1 : unconst(nptr, wchar_t *);
  return acc;
}
