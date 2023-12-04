/* Copyright 2023 Ray Chason. See COPYING.DJ for details. */

#include <wctype.h>

int
iswdigit(wint_t c)
{
  return L'0' <= c && c <= '9';
}
