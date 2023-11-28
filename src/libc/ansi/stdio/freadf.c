/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#define __DJ_CHECKED_FUNCTION
#include <stdio.h>
#include <stdlib.h>

size_t
__fread_chk(void * restrict ptr, size_t size, size_t nelem, FILE * restrict stream, size_t ptrsize)
{
  size_t rsize = size * nelem;
  if (nelem != 0 && rsize/nelem != size) {
    fputs("fread: product of element size and element count overflows\n", stderr);
    abort();
  }

  if (ptrsize != (size_t)(-1) && rsize > ptrsize) {
    fputs("fread called with buffer size too small\n", stderr);
    abort();
  }

  return fread(ptr, size, nelem, stream);
}
