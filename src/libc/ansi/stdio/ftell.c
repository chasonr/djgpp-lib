/* Copyright (C) 2014 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <libc/stubs.h>
#include <stdio.h>
#include <unistd.h>
#include <libc/file.h>
#include <fcntl.h>
#include <libc/dosio.h>
#include <libc/fd_props.h>
#include "../../c99/wchar/codepage.h"

long
ftell(FILE *f)
{
  const int fd = fileno(f);
  long tres;
  int adjust = 0;

  /* If this is a FILE for a directory, we have no concept of position.
   * The stream I/O functions cannot be used to read/write a FILE
   * for directories. So, just return position 0. */
  if (__get_fd_flags(fd) & FILE_DESC_DIRECTORY)
    return 0;

  if (f->_cnt < 0)
    f->_cnt = 0;
  if (f->_flag & _IOREAD)
    adjust = - f->_cnt;
  else if (f->_flag & (_IOWRT | _IORW))
  {
    if (f->_flag & _IOWRT && f->_base && (f->_flag & _IONBF) == 0)
      adjust = f->_ptr - f->_base;
  }
  else
    return -1;
  tres = lseek(fd, 0L, 1);
  if (tres < 0)
    return tres;
  tres += adjust;
  if (__dj_is_utf8()) {
    for (unsigned i = 0; i < f->_wungetsize; ++i) {
      unsigned w = f->_wunget[i];
      if (w < 0x80) {
        --tres;
      } else if (w < 0x800) {
        tres -= 2;
      } else if (0xD800 <= w && w <= 0xDFFF) {
        tres -= 2;
      } else {
        tres -= 3;
      }
    }
  } else {
    tres -= f->_wungetsize;
  }
  return tres;
}
