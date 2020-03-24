/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2007 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2005 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdlib.h>
#include <wchar.h>

size_t
wcstombs(char *s, const wchar_t *wcs, size_t n)
{
  static mbstate_t shift;
  return wcsrtombs(s, &wcs, n, &shift);
}
