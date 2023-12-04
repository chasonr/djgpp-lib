/* Copyright 2023 Ray Chason. See COPYING.DJ for details. */

#include <wctype.h>

int
iswgraph(wint_t c)
{
  return iswprint(c) && !iswspace(c);
}
