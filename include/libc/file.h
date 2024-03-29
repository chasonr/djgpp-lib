/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_libc_file_h__
#define __dj_include_libc_file_h__

#include <wchar.h>
#include <fcntl.h>
#include <libc/dosio.h>
#include <libc/ttyprvt.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __dj_ENFORCE_ANSI_FREESTANDING

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) \
  || !defined(__STRICT_ANSI__) || defined(__cplusplus)

#endif /* (__STDC_VERSION__ >= 199901L) || !__STRICT_ANSI__ */

#ifndef __STRICT_ANSI__

#ifndef _POSIX_SOURCE

#define _IOREAD   000010
#define _IOWRT    000020
#define _IOMYBUF  000040
#define _IOEOF    000100
#define _IOERR    000200
#define _IOSTRG   000400
#define _IORW     001000
#define _IORMONCL 004000  /* remove on close, for temp files */
/* if _flag & _IORMONCL, ._name_to_remove needs freeing */
#define _IOUNGETC 010000  /* there is an ungetc'ed character in the buffer */
#define _IOTERM   020000  /* file's handle hooked by termios */
#define _IONTERM  040000  /* file's handle not hooked by termios */
#define _IOBYTE   0100000 /* file is byte-oriented */
#define _IOWIDE   0200000 /* file is wide-oriented */

int  _flsbuf(int, FILE*);
int  _filbuf(FILE *);
void _fwalk(void (*)(FILE *));

static __inline__ int __getc_raw(FILE *const p)
{
  if (p->_cnt > 0)
  {
    p->_cnt--;
    return (unsigned char)*(p->_ptr++);
  }
  return _filbuf(p);
}

static __inline__ int __putc_raw(int const x, FILE *const p)
{
  if (p->_cnt > 0)
  {
    p->_cnt--;
    return (unsigned char)(*(p->_ptr++) = (unsigned char)x);
  }
  return _flsbuf((unsigned char)x, p);
}

static __inline__ int __is_text_file(FILE *const p)
{
  return !(p->_flag & (_IOSTRG | _IOTERM))
         && (__file_handle_modes[p->_file] & O_TEXT);
}

static __inline__ int __getc(FILE *const p)
{
  int __c;
  if (__libc_read_termios_hook
      && !(p->_flag & (_IOTERM | _IONTERM)))
  {
    extern int __isatty(int);
    /* first time we see this handle--see if termios hooked it */
    if (!(p->_flag & _IOSTRG) && __isatty(p->_file))
      p->_flag |= _IOTERM;
    else
      p->_flag |= _IONTERM;
  }
  __c = __getc_raw(p);
  if (__c == '\r' && __is_text_file(p))
    return __getc_raw(p);
  return __c;
}

static __inline__ int __putc(const int x, FILE *const p)
{
  if (__libc_write_termios_hook
      && !(p->_flag & (_IOTERM | _IONTERM)))
  {
    extern int __isatty(int);
    /* first time we see this handle--see if termios hooked it */
    if (!(p->_flag & _IOSTRG) && __isatty(p->_file))
      p->_flag |= _IOTERM;
    else
      p->_flag |= _IONTERM;
  }
  if (x == '\n' && __is_text_file(p))
    __putc_raw('\r', p);
  return __putc_raw(x, p);
}

static __inline__ void __stropenw(FILE *p, char *str, int len)
{
  p->_flag = _IOWRT | _IOSTRG | _IONTERM;
  p->_ptr = str;
  p->_cnt = len;
}

static __inline__ void __strclosew(FILE *p)
{
  *p->_ptr = '\0';
}

static __inline__ void __stropenr(FILE *p, const char *str)
{
  union {
    char *s;
    const char *cs;
  } u;

  u.cs = str;
  p->_flag = _IOREAD | _IOSTRG | _IONTERM | _IOBYTE;
  p->_ptr = p->_base = u.s;
  p->_cnt = 0;
  while (*str++)
    p->_cnt++;
  p->_bufsiz = p->_cnt;
}

static __inline__ void __stropenwr(FILE *p, const wchar_t *str)
{
  p->_flag = _IOREAD | _IOSTRG | _IONTERM | _IOWIDE;
  p->_ptr = p->_base = (char *)str;
  p->_cnt = 0;
  while (*str++)
    p->_cnt += sizeof(wchar_t);
  p->_bufsiz = p->_cnt;
}

#undef  fileno
#define fileno(f)       (f->_file)
#undef  feof
#define feof(f)         (((f)->_flag & _IOEOF) != 0)
#undef  ferror
#define ferror(f)       (((f)->_flag & _IOERR) != 0)

#endif /* !_POSIX_SOURCE */
#endif /* !__STRICT_ANSI__ */
#endif /* !__dj_ENFORCE_ANSI_FREESTANDING */

#ifndef __dj_ENFORCE_FUNCTION_CALLS
#endif /* !__dj_ENFORCE_FUNCTION_CALLS */

#ifdef __cplusplus
}
#endif

#endif /* __dj_include_libc_file_h__ */
