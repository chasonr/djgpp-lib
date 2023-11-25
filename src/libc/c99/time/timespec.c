/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <libc/stubs.h>
#include <time.h>
#include <dpmi.h>

int timespec_get(struct timespec *ts, int base)
{
  __dpmi_regs r;
  struct tm tmblk;

  if (base != TIME_UTC) {
    return -1;
  }

  r.h.ah = 0x2c;
  __dpmi_int(0x21, &r);
		
  ts->tv_nsec = r.h.dl * 10000000;
  tmblk.tm_sec = r.h.dh;
  tmblk.tm_min = r.h.cl;
  tmblk.tm_hour = r.h.ch;

  r.h.ah = 0x2a;
  __dpmi_int(0x21, &r);

  tmblk.tm_mday = r.h.dl;
  tmblk.tm_mon = r.h.dh - 1;
  tmblk.tm_year = (r.x.cx & 0x7ff) - 1900;

  tmblk.tm_wday = tmblk.tm_yday = tmblk.tm_gmtoff = 0;
  tmblk.tm_zone = 0;
  tmblk.tm_isdst = -1;

  ts->tv_sec = mktime(&tmblk);

  return 0;
}
