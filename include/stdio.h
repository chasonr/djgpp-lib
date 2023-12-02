/* Copyright (C) 2014 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2000 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */

#ifndef __dj_include_stdio_h_
#define __dj_include_stdio_h_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __dj_ENFORCE_ANSI_FREESTANDING

#include <sys/version.h>
#include <sys/djtypes.h>
#include <sys/fortify.h>
#include <sys/attrib.h>
  
#define _IOFBF    	00001  /*  File is full buffered.  */
#define _IONBF    	00002  /*  File is not buffered.  */
#define _IOLBF    	00004  /*  File is line buffered.  */

/* Some programs think they know better... */
#undef NULL
#if (__GNUC__ >= 4) && defined(__cplusplus)
#  define NULL          __null
#elif defined(__cplusplus)
#  define NULL          0
#else
#  define NULL          ((void*)0)
#endif

#define BUFSIZ		16384
#define EOF		(-1)
#define FILENAME_MAX	260
#define FOPEN_MAX	20
#define L_tmpnam	260
#define TMP_MAX		999999

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

#ifndef _VA_LIST
__DJ_va_list
#define _VA_LIST
#endif

#ifndef _SIZE_T
__DJ_size_t
#define _SIZE_T
#endif

#ifndef _SSIZE_T
__DJ_ssize_t
#define _SSIZE_T
#endif

#ifndef _DJ_MBSTATE_T
__DJ_mbstate_t
#define _DJ_MBSTATE_T
#endif

/* Note that the definitions of these fields are NOT guaranteed!  They
   may change with any release without notice!  The fact that they
   are here at all is to comply with ANSI specifictions. */
   
typedef struct __dj_FILE {
  ssize_t  _cnt;
  char    *_ptr;
  char    *_base;
  size_t   _bufsiz;
  int      _flag;
  int      _file;
  char    *_name_to_remove;
  size_t   _fillsize;
  __dj_mbstate_t _mbstate;
  unsigned short _wunget[2];
  unsigned _wungetsize;
} FILE;

typedef struct __dj_fpos_t {
  unsigned long _pos;
  __dj_mbstate_t _mbstate;
} fpos_t;

extern FILE __dj_stdin, __dj_stdout, __dj_stderr;
#define stdin	(&__dj_stdin)
#define stdout	(&__dj_stdout)
#define stderr	(&__dj_stderr)

void	clearerr(FILE *_stream);
int	fclose(FILE *_stream);
int	feof(FILE *_stream);
int	ferror(FILE *_stream);
int	fflush(FILE *_stream);
int	fgetc(FILE *_stream);
int	fgetpos(FILE *_stream, fpos_t *_pos);
char *	fgets(char * __restrict__ _s, int _n, FILE * __restrict__ _stream);
FILE *	fopen(const char *_filename, const char *_mode);
int	fprintf(FILE * __restrict__ _stream, const char * __restrict__ _format, ...);
int	fputc(int _c, FILE *_stream);
int	fputs(const char *_s, FILE *_stream);
size_t	fread(void * __restrict__ _ptr, size_t _size, size_t _nelem, FILE * __restrict__ _stream);
FILE *	freopen(const char *_filename, const char *_mode, FILE *_stream);
int	fscanf(FILE *_stream, const char *_format, ...);
int	fseek(FILE *_stream, long _offset, int _mode);
int	fsetpos(FILE *_stream, const fpos_t *_pos);
long	ftell(FILE *_stream);
size_t	fwrite(const void *_ptr, size_t _size, size_t _nelem, FILE *_stream);
int	getc(FILE *_stream);
int	getchar(void);
#if __STDC_VERSION__ < 201112L
char *	gets(char *_s)
        __dj_attr_deprecated("the gets function is dangerous and should not be used");
#endif
void	perror(const char *_s);
int	printf(const char * __restrict__ _format, ...);
int	putc(int _c, FILE *_stream);
int	putchar(int _c);
int	puts(const char *_s);
int	remove(const char *_filename);
int	rename(const char *_old, const char *_new);
void	rewind(FILE *_stream);
int	scanf(const char *_format, ...);
void	setbuf(FILE *_stream, char *_buf);
int	setvbuf(FILE *_stream, char *_buf, int _mode, size_t _size);
int	sprintf(char * __restrict__ _s, const char * __restrict__ _format, ...);
int	sscanf(const char *_s, const char *_format, ...);
FILE *	tmpfile(void);
char *	tmpnam(char *_s);
int	ungetc(int _c, FILE *_stream);
int	vfprintf(FILE * __restrict__ _stream, const char * __restrict__ _format, va_list _ap);
int	vprintf(const char * __restrict__ _format, va_list _ap);
int	vsprintf(char * __restrict__ _s, const char * __restrict__ _format, va_list _ap);

#if __DJ_USE_FORTIFY_LEVEL > 0 || defined(__DJ_CHECKED_FUNCTION)
extern char *__fgets_chk(char * __restrict__ _s, int _n, FILE * __restrict__ _stream, size_t _ssize);
extern char *__gets_chk(char *_s, size_t _ssize);
extern size_t __fread_chk(void * __restrict__ _ptr, size_t _size, size_t _nelem, FILE * __restrict__ _stream, size_t _ptrsize);
extern int __sprintf_chk(char * __restrict__ _s, int _flag, size_t _ssize, const char * __restrict__ _format, ...);
extern int __vsprintf_chk(char * __restrict__ _s, int _flag, size_t _ssize, const char * __restrict__ _format, va_list _ap);
extern int __fprintf_chk(FILE * __restrict__ _stream, int _flag, const char * __restrict__ _format, ...);
extern int __printf_chk(int _flag, const char * __restrict__ _format, ...);
extern int __vfprintf_chk(FILE * __restrict__ _stream, int _flag, const char * __restrict__ _format, va_list _ap);
extern int __vprintf_chk(int _flag, const char * __restrict__ _format, va_list _ap);
extern int __doprnt_chk(const char *_fmt0, va_list argp, FILE *_fp, int _flag);
#endif

#if __DJ_USE_FORTIFY_LEVEL > 0

extern size_t __fgets_chk_warn(char * __restrict__ _s, int _n, FILE * __restrict__ _stream, size_t _ssize)
        __dj_forward(__fgets_chk)
        __attribute__((__warning__("fgets called with length bigger than size of destination buffer")));
extern size_t __fgets_alias(char * __restrict__ _s, int _n, FILE * __restrict__ _stream)
        __dj_forward(fgets);

__dj_fortify_function char *
fgets(char * __restrict__ _s, int _n, FILE * __restrict__ _stream)
{
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(fgets, _n, sizeof(_s[0]), _sz, _s, _n, _stream);
}

#if __STDC_VERSION__ < 201112L
char *__gets_alias(char *_s) __dj_forward(gets);

__dj_fortify_function char *
gets(char *_s)
{
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);
  if (_sz == (size_t)-1) {
    return __gets_alias(_s);
  } else {
    return __gets_chk(_s, _sz);
  }
}
#endif

extern size_t __fread_chk_warn(void * __restrict__ _ptr, size_t _size, size_t _nelem, FILE * __restrict__ _stream, size_t _ptrsize)
        __dj_forward(__fread_chk)
        __attribute__((__warning__("fread called with length bigger than size of destination buffer")));
extern size_t __fread_alias(void * __restrict__ _ptr, size_t _size, size_t _nelem, FILE * __restrict__ _stream)
        __dj_forward(fread);

__dj_fortify_function size_t
fread(void * __restrict__ _ptr, size_t _size, size_t _nelem, FILE * __restrict__ _stream)
{
  /* Forming _rsize as a size_t may cause an overflow; but unsigned long long
     can handle any product of two size_t operands */
  unsigned long long _rsize = (unsigned long long)_size * _nelem;

  size_t _sz = __dj_bos(_ptr, 0);
  return __dj_fortify_n(fread, _rsize, 1, _sz,
                        _ptr, _size, _nelem, _stream);
}

__dj_fortify_function int
sprintf(char * __restrict__ _s, const char * __restrict__ _format, ...)
{
  int _flag = (__DJ_USE_FORTIFY_LEVEL > 1) && !__builtin_constant_p(_format);
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);

  return __builtin___sprintf_chk(_s, _flag, _sz, _format, __builtin_va_arg_pack());
}

__dj_fortify_function int
vsprintf(char * __restrict__ _s, const char * __restrict__ _format, va_list _ap)
{
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);

  return __builtin___vsprintf_chk(_s, 0, _sz, _format, _ap);
}

#if __DJ_USE_FORTIFY_LEVEL > 1

__dj_fortify_function int
fprintf(FILE * __restrict__ _stream, const char * __restrict__ _format, ...)
{
  int _flag = !__builtin_constant_p(_format);
  return __builtin___fprintf_chk(_stream, _flag, _format, __builtin_va_arg_pack());
}

__dj_fortify_function int
printf(const char * __restrict__ _format, ...)
{
  int _flag = !__builtin_constant_p(_format);
  return __builtin___printf_chk(_flag, _format, __builtin_va_arg_pack());
}

__dj_fortify_function int
vfprintf(FILE * __restrict__ _stream, const char * __restrict__ _format, va_list _ap)
{
  int _flag = 0;
  return __builtin___vfprintf_chk(_stream, _flag, _format, _ap);
}

__dj_fortify_function int
vprintf(const char * __restrict__ _format, va_list _ap)
{
  int _flag = 0;
  return __builtin___vprintf_chk(_flag, _format, _ap);
}

#endif

#endif

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) \
  || !defined(__STRICT_ANSI__) || defined(__cplusplus)

int	snprintf(char * __restrict__ _str, size_t _n, const char * __restrict__ _fmt, ...);
int	vfscanf(FILE *_stream, const char *_format, va_list _ap);
int	vscanf(const char *_format, va_list _ap);
int	vsnprintf(char * __restrict__ _str, size_t _n, const char * __restrict__ _fmt, va_list _ap);
int	vsscanf(const char *_s, const char *_format, va_list _ap);

#if __DJ_USE_FORTIFY_LEVEL > 0 || defined(__DJ_CHECKED_FUNCTION)
extern int __snprintf_chk(char * __restrict__ _str, size_t _n, int _flag, size_t _strsize, const char * __restrict__ _format, ...);
extern int __vsnprintf_chk(char * __restrict__ _str, size_t _n, int _flag, size_t _strsize, const char * __restrict__ _format, va_list _ap);
#endif

#if __DJ_USE_FORTIFY_LEVEL > 0

__dj_fortify_function int
snprintf(char * __restrict__ _str, size_t _n, const char * __restrict__ _fmt, ...)
{
  int _flag = (__DJ_USE_FORTIFY_LEVEL > 1) && !__builtin_constant_p(_fmt);
  size_t _sz = __dj_bos(_str, __DJ_USE_FORTIFY_LEVEL > 1);

  return __builtin___snprintf_chk(_str, _n, _flag, _sz, _fmt, __builtin_va_arg_pack());
}

__dj_fortify_function int
vsnprintf(char * __restrict__ _str, size_t _n, const char * __restrict__ _fmt, va_list _ap)
{
  size_t _sz = __dj_bos(_str, __DJ_USE_FORTIFY_LEVEL > 1);

  return __builtin___vsnprintf_chk(_str, _n, 0, _sz, _fmt, _ap);
}

#endif

#endif /* (__STDC_VERSION__ >= 199901L) || !__STRICT_ANSI__ */

#ifndef __STRICT_ANSI__

#define L_ctermid 20
#define L_cusrid
/* #define STREAM_MAX	20 - DOS can change this */

int	dprintf(int _fd, const char * __restrict__ _format, ...) __attribute__ ((__format__ (__printf__, 2, 3)));
int	fileno(FILE *_stream);
FILE *	fdopen(int _fildes, const char *_type);
int	mkstemp(char *_template);
int	pclose(FILE *_pf);
FILE *	popen(const char *_command, const char *_mode);
char *	tempnam(const char *_dir, const char *_prefix);
int	vdprintf(int _fd, const char * __restrict__ _format, va_list _ap) __attribute__ ((__format__ (__printf__, 2, 0)));

#if __DJ_USE_FORTIFY_LEVEL > 1 || defined(__DJ_CHECKED_FUNCTION)
extern int __dprintf_chk(int _fd, int _flag, const char * __restrict__ _format, ...);
extern int __vdprintf_chk(int _fd, int _flag, const char * __restrict__ _format, va_list _ap);
#endif

#if __DJ_USE_FORTIFY_LEVEL > 1

__dj_fortify_function int
dprintf(int _fd, const char * __restrict__ _format, ...)
{
  int _flag = !__builtin_constant_p(_format);
  return __dprintf_chk(_fd, _flag, _format, __builtin_va_arg_pack());
}

__dj_fortify_function int
vdprintf(int _fd, const char * __restrict__ _format, va_list _ap)
{
  int _flag = !__builtin_constant_p(_format);
  return __vdprintf_chk(_fd, _flag, _format, _ap);
}

#endif

#ifndef _POSIX_SOURCE

extern FILE __dj_stdprn, __dj_stdaux;
#define stdprn	(&__dj_stdprn)
#define stdaux	(&__dj_stdaux)

#define P_tmpdir "c:/"

void	_djstat_describe_lossage(FILE *_to_where);
int	_doprnt(const char *_fmt, va_list _args, FILE *_f);
int	_doscan(FILE *_f, const char *_fmt, va_list _args);
int	_doscan_low(FILE *, int (*)(FILE *_get), int (*_unget)(int, FILE *), const char *_fmt, va_list _args);
int	fpurge(FILE *_f);
int	getw(FILE *_f);
char *	mktemp(char *_template);
int	putw(int _v, FILE *_f);
void	setbuffer(FILE *_f, void *_buf, int _size);
void	setlinebuf(FILE *_f);
int	_rename(const char *_old, const char *_new);	/* Simple (no directory) */
int	asprintf(char ** __restrict__ _sp, const char * __restrict__ _format, ...) __attribute__((format (__printf__, 2, 3)));
char *	asnprintf(char * __restrict__ _s, size_t * __restrict__ _np, const char * __restrict__ _format, ...) __attribute__((format (__printf__, 3, 4)));
int	vasprintf(char ** __restrict__ _sp, const char * __restrict__ _format, va_list _ap) __attribute__((format (__printf__, 2, 0)));
char *	vasnprintf(char * __restrict__ _s, size_t * __restrict__ _np, const char * __restrict__ _format, va_list _ap) __attribute__((format (__printf__, 3, 0)));

#if __DJ_USE_FORTIFY_LEVEL > 1 || defined(__DJ_CHECKED_FUNCTION)
extern int __asprintf_chk(char ** __restrict__ _sp, int _flag, const char * __restrict__ _format, ...);
extern char *__asnprintf_chk(char * __restrict__ _s, size_t * __restrict__ _np, int _flag, size_t _ssize, const char * __restrict__ _format, ...);
extern int __vasprintf_chk(char ** __restrict__ _sp, int _flag, const char * __restrict__ _format, va_list _ap);
extern char *__vasnprintf_chk(char * __restrict__ _s, size_t * __restrict__ _np, int _flag, size_t _ssize, const char * __restrict__ _format, va_list _ap);
#endif

#if __DJ_USE_FORTIFY_LEVEL > 1

__dj_fortify_function int
asprintf(char ** __restrict__ _sp, const char * __restrict__ _format, ...)
{
  int _flag = !__builtin_constant_p(_format);
  return __asprintf_chk(_sp, _flag, _format, __builtin_va_arg_pack());
}

__dj_fortify_function char *
asnprintf(char * __restrict__ _s, size_t * __restrict__ _np, const char * __restrict__ _format, ...)
{
  int _flag = (__DJ_USE_FORTIFY_LEVEL > 1) && !__builtin_constant_p(_format);
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);
  return __asnprintf_chk(_s, _np, _flag, _format, __builtin_va_arg_pack());
}

__dj_fortify_function int
vasprintf(char ** __restrict__ _sp, const char * __restrict__ _format, va_list _ap)
{
  int _flag = 0;
  return __vasprintf_chk(_sp, _flag, _format, _ap);
}

__dj_fortify_function char *
vasnprintf(char * __restrict__ _s, size_t * __restrict__ _np, const char * __restrict__ _format, va_list _ap)
{
  int _flag = 0;
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);
  return __vasnprintf_chk(_s, _np, _flag, _sz, _format, _ap);
}

#endif

#ifndef _OFF_T
__DJ_off_t
#define _OFF_T
#endif
#ifndef _OFF64_T
__DJ_off64_t
#define _OFF64_T
#endif
int	fseeko(FILE *_stream, off_t _offset, int _mode);
off_t	ftello(FILE *_stream);
int	fseeko64(FILE *_stream, off64_t _offset, int _mode);
off64_t	ftello64(FILE *_stream);

#endif /* !_POSIX_SOURCE */
#endif /* !__STRICT_ANSI__ */
#endif /* !__dj_ENFORCE_ANSI_FREESTANDING */

#ifndef __dj_ENFORCE_FUNCTION_CALLS
#endif /* !__dj_ENFORCE_FUNCTION_CALLS */

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_stdio_h_ */
