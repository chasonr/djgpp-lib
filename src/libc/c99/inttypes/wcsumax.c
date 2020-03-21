/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
#include <inttypes.h>
#include <wchar.h>

uintmax_t
wcstoumax (const wchar_t *nptr, wchar_t **endptr, int base)
{
  return(wcstoull(nptr, endptr, base));
}
