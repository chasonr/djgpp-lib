/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
#include <inttypes.h>
#include <wchar.h>

intmax_t
wcstoimax (const wchar_t *nptr, wchar_t **endptr, int base)
{
  return(wcstoll(nptr, endptr, base));
}
