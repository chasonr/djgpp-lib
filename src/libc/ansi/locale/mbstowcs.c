/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 2007 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2005 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdlib.h>
#include <wchar.h>

size_t
mbstowcs(wchar_t *wcs, const char *s, size_t n)
{
  static mbstate_t shift;
  return mbsrtowcs(wcs, &s, n, &shift);
}
