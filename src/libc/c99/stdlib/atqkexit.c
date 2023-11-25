/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdlib.h>
#include <libc/atexit.h>

int
at_quick_exit(void (*a)(void))
{
  struct __atexit *ap;
  if (a == 0)
    return -1;
  ap = (struct __atexit *)malloc(sizeof(struct __atexit));
  if (!ap)
    return -1;
  ap->__next = __at_quick_exit_ptr;
  ap->__function = a;
  __at_quick_exit_ptr = ap;
  return 0;
}
