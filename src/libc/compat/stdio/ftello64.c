/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2007 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2006 DJ Delorie, see COPYING.DJ for details */
#include <libc/stubs.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "../../c99/wchar/codepage.h"

off64_t
ftello64(FILE *_stream)
{
  /* FIXME ??? */
  int r;
  r = fflush(_stream);
  if (r != 0)
    return -1;
  off64_t pos = llseek(fileno(_stream), 0, SEEK_CUR);
  if (__dj_is_utf8()) {
    for (unsigned i = 0; i < _stream->_wungetsize; ++i) {
      unsigned w = _stream->_wunget[i];
      if (w < 0x80) {
        --pos;
      } else if (w < 0x800) {
        pos -= 2;
      } else if (0xD800 <= w && w <= 0xDFFF) {
        pos -= 2;
      } else {
        pos -= 3;
      }
    }
  } else {
    pos -= _stream->_wungetsize;
  }
  return pos;
}

