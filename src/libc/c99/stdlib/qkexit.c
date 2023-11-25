/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <io.h>
#include <libc/atexit.h>

struct __atexit *__at_quick_exit_ptr = 0;

void
quick_exit(int status)
{
  struct __atexit *a,*o;

  a = __at_quick_exit_ptr;
  __at_quick_exit_ptr = 0; /* to prevent infinite loops */
  while (a)
  {
    (a->__function)();
    o = a;
    a = a->__next;
    free(o);
  }

  /* in case the program set it this way */
  setmode(0, O_TEXT);
  _exit(status);
}
