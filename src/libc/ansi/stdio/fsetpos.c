/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <errno.h>

int
fsetpos(FILE *stream, const fpos_t *pos)
{
  if (stream && pos)
  {
    stream->_mbstate = pos->_mbstate;
    return fseek(stream, (long)(pos->_pos), SEEK_SET);
  }
  errno = EFAULT;
  return -1;
}
