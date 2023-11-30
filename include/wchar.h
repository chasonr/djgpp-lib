/* Copyright (C) 2012 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_wchar_h_
#define __dj_include_wchar_h_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __dj_ENFORCE_ANSI_FREESTANDING

#include <sys/djtypes.h>
#include <sys/fortify.h>

/* Some programs think they know better... */
#undef NULL
#if (__GNUC__ >= 4) && defined(__cplusplus)
#  define NULL          __null
#elif defined(__cplusplus)
#  define NULL          0
#else
#  define NULL          ((void*)0)
#endif

#ifndef _SIZE_T
__DJ_size_t
#define _SIZE_T
#endif

#ifndef _WCHAR_T
__DJ_wchar_t
#define _WCHAR_T
#endif

#ifndef _WINT_T
__DJ_wint_t
#define _WINT_T
#endif

#ifndef WEOF
#define WEOF ((wint_t)(-1))
#endif

#ifndef _MBSTATE_T
#ifndef _DJ_MBSTATE_T
__DJ_mbstate_t
#define _DJ_MBSTATE_T
#endif
typedef __dj_mbstate_t mbstate_t;
#define _MBSTATE_T
#endif

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) \
  || !defined(__STRICT_ANSI__) || defined(__cplusplus)

/* Declared as an incomplete type, for wcsftime */
struct tm;

  /* These are defined by stdint.h, so make them conditional.  */
#ifndef WCHAR_MAX
#define WCHAR_MAX	65535
#endif
#ifndef WCHAR_MIN
#define WCHAR_MIN	0
#endif

/* ISO C does not specify va_list as defined in wchar.h, but some prototypes
   use it, and it is defined this way in stdio.h */
#ifndef _VA_LIST
__DJ_va_list
#define _VA_LIST
#endif

/* FILE as an incomplete type */
struct __dj_FILE;

int fwprintf(struct __dj_FILE * __restrict__ _stream, const wchar_t * __restrict__ _format, ...);
int fwscanf(struct __dj_FILE * __restrict__ _stream, const wchar_t * __restrict__ _format, ...);
int swprintf(wchar_t * __restrict__ _s, size_t _n, const wchar_t * __restrict__ _format, ...);
int swscanf(const wchar_t * __restrict__ _s, const wchar_t * __restrict__ _format, ...);
int vfwprintf(struct __dj_FILE * __restrict__ _stream, const wchar_t * __restrict__ _format, va_list _arg);
int vfwscanf(struct __dj_FILE * __restrict__ _stream, const wchar_t * __restrict__ _format, va_list _arg);
int vswprintf(wchar_t * __restrict__ _s, size_t _n, const wchar_t * __restrict__ _format, va_list _arg);
int vswscanf(const wchar_t * __restrict__ _s, const wchar_t * __restrict__ _format, va_list _arg);
int vwprintf(const wchar_t * __restrict__ _format, va_list _arg);
int vwscanf(const wchar_t * __restrict__ _format, va_list _arg);
int wprintf(const wchar_t * __restrict__ _format, ...);
int wscanf(const wchar_t * __restrict__ _format, ...);
wint_t fgetwc(struct __dj_FILE *_stream);
wchar_t * fgetws(wchar_t * __restrict__ _s, int _n, struct __dj_FILE * __restrict__ _stream);
wint_t fputwc(wchar_t _c, struct __dj_FILE *_stream);
int fputws(const wchar_t * __restrict__ _s, struct __dj_FILE * __restrict__ _stream);
int fwide(struct __dj_FILE *_stream, int _mode);
wint_t getwc(struct __dj_FILE *_stream);
wint_t getwchar(void);
wint_t putwc(wchar_t _c, struct __dj_FILE *_stream);
wint_t putwchar(wchar_t _c);
wint_t ungetwc(wint_t _c, struct __dj_FILE *_stream);
double wcstod(const wchar_t * __restrict__ _nptr, wchar_t ** __restrict__ _endptr);
float wcstof(const wchar_t * __restrict__ _nptr, wchar_t ** __restrict__ _endptr);
long double wcstold(const wchar_t * __restrict__ _nptr, wchar_t ** __restrict__ _endptr);
long wcstol(const wchar_t * __restrict__ _nptr, wchar_t ** __restrict__ _endptr, int _base);
long long wcstoll(const wchar_t * __restrict__ _nptr, wchar_t ** __restrict__ _endptr, int _base);
unsigned long wcstoul(const wchar_t * __restrict__ _nptr, wchar_t ** __restrict__ _endptr, int _base);
unsigned long long wcstoull(const wchar_t * __restrict__ _nptr, wchar_t ** __restrict__ _endptr, int _base);
wchar_t * wcscpy(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2);
wchar_t * wcsncpy(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n);
wchar_t * wmemcpy(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n);
wchar_t * wmemmove(wchar_t *_s1, const wchar_t *_s2, size_t _n);
wchar_t * wcscat(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2);
wchar_t * wcsncat(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n);
int wcscmp(const wchar_t *_s1, const wchar_t *_s2);
int wcscoll(const wchar_t *_s1, const wchar_t *_s2);
int wcsncmp(const wchar_t *_s1, const wchar_t *_s2, size_t _n);
size_t wcsxfrm(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n);
int wmemcmp(const wchar_t *_s1, const wchar_t *_s2, size_t _n);
wchar_t * wcschr(const wchar_t *_s, wchar_t _c);
size_t wcscspn(const wchar_t *_s1, const wchar_t *_s2);
wchar_t * wcspbrk(const wchar_t *_s1, const wchar_t *_s2);
wchar_t * wcsrchr(const wchar_t *_s, wchar_t _c);
size_t wcsspn(const wchar_t *_s1, const wchar_t *_s2);
wchar_t * wcsstr(const wchar_t *_s1, const wchar_t *_s2);
wchar_t * wcstok(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, wchar_t ** __restrict__ _ptr);
wchar_t * wmemchr(const wchar_t *_s, wchar_t _c, size_t _n);
size_t wcslen(const wchar_t *_s);
wchar_t * wmemset(wchar_t *_s, wchar_t _c, size_t _n);
size_t wcsftime(wchar_t * __restrict__ _s, size_t _maxsize, const wchar_t * __restrict__ _format, const struct tm * __restrict__ _timeptr);
wint_t btowc(int _c);
int wctob(wint_t _c);
int mbsinit(const mbstate_t *_ps);
size_t mbrlen(const char * __restrict__ _s, size_t _n, mbstate_t * __restrict__ _ps);
size_t mbrtowc(wchar_t * __restrict__ _pwc, const char * __restrict__ _s, size_t _n, mbstate_t * __restrict__ _ps);
size_t wcrtomb(char * __restrict__ _s, wchar_t _wc, mbstate_t * __restrict__ _ps);
size_t mbsrtowcs(wchar_t * __restrict__ _dst, const char ** __restrict__ _src, size_t _len, mbstate_t * __restrict__ _ps);
size_t wcsrtombs(char * __restrict__ _dst, const wchar_t ** __restrict__ _src, size_t _len, mbstate_t * __restrict__ _ps);

#if defined(__DJ_CHECKED_FUNCTION) || __DJ_USE_FORTIFY_LEVEL > 0
extern int __fwprintf_chk(struct __dj_FILE * __restrict__ _stream, int _flag, const wchar_t * __restrict__ _format, ...);
extern int __swprintf_chk(wchar_t * __restrict__ _s, size_t _n, int _flag, size_t _ssize, const wchar_t * __restrict__ _format, ...);
extern int __vfwprintf_chk(struct __dj_FILE * __restrict__ _stream, int _flag, const wchar_t * __restrict__ _format, va_list _arg);
extern int __vswprintf_chk(wchar_t * __restrict__ _s, size_t _n, int _flag, size_t _ssize, const wchar_t * __restrict__ _format, va_list _arg);
extern int __vwprintf_chk(int _flag, const wchar_t * __restrict__ _format, va_list _arg);
extern int __wprintf_chk(int _flag, const wchar_t * __restrict__ _format, ...);
extern wchar_t * __fgetws_chk(wchar_t * __restrict__ _s, int _n, struct __dj_FILE * __restrict__ _stream, size_t _ssize);
extern wchar_t * __wcscpy_chk(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _s1size);
extern wchar_t * __wcsncpy_chk(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n, size_t _s1size);
extern wchar_t * __wmemcpy_chk(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n, size_t _s1size);
extern wchar_t * __wmemmove_chk(wchar_t *_s1, const wchar_t *_s2, size_t _n, size_t _s1size);
extern wchar_t * __wcscat_chk(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _s1size);
extern wchar_t * __wcsncat_chk(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n, size_t _s1size);
extern size_t __wcsxfrm_chk(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n, size_t _s1size);
extern wchar_t * __wmemset_chk(wchar_t *_s, wchar_t _c, size_t _n, size_t _ssize);
extern size_t __wcsftime_chk(wchar_t * __restrict__ _s, size_t _maxsize, const wchar_t * __restrict__ _format, const struct tm * __restrict__ _timeptr, size_t _ssize);
extern size_t __wcrtomb_chk(char * __restrict__ _s, wchar_t _wc, mbstate_t * __restrict__ _ps, size_t _ssize);
extern size_t __mbsrtowcs_chk(wchar_t * __restrict__ _dst, const char ** __restrict__ _src, size_t _len, mbstate_t * __restrict__ _ps, size_t _dstsize);
extern size_t __wcsrtombs_chk(char * __restrict__ _dst, const wchar_t ** __restrict__ _src, size_t _len, mbstate_t * __restrict__ _ps, size_t _dstsize);
#endif

#if __DJ_USE_FORTIFY_LEVEL > 0

int __swprintf_chk_warn(wchar_t * __restrict__ _s, size_t _n, int _flag, size_t _ssize, const wchar_t * __restrict__ _format, ...)
        __dj_forward(__swprintf_chk)
        __attribute__((warning("swprintf called with length bigger than size of buffer")));
int __swprintf_alias(wchar_t * __restrict__ _s, size_t _n, const wchar_t * __restrict__ _format, ...)
        __dj_forward(swprintf);

__dj_fortify_function int
swprintf(wchar_t * __restrict__ _s, size_t _n, const wchar_t * __restrict__ _format, ...)
{
  int _flag = (__DJ_USE_FORTIFY_LEVEL > 1) && !__builtin_constant_p(_format);
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);

  if ((((__typeof(_n))0 < (__typeof(_n))-1) || (__builtin_constant_p(_n) && _n >= 0)) \
  &&  __builtin_constant_p(_n <= _sz/sizeof(wchar_t))) {
    if (_n <= _sz/sizeof(wchar_t)) {
      if (_flag) {
        return __swprintf_chk(_s, _n, _flag, _sz/sizeof(wchar_t), _format, __builtin_va_arg_pack());
      } else {
        return __swprintf_alias(_s, _n, _format, __builtin_va_arg_pack());
      }
    } else {
      return __swprintf_chk_warn(_s, _n, _flag, _sz/sizeof(wchar_t), _format, __builtin_va_arg_pack());
    }
  } else {
    return __swprintf_chk(_s, _n, _flag, _sz/sizeof(wchar_t), _format, __builtin_va_arg_pack());
  }
}

int __vswprintf_chk_warn(wchar_t * __restrict__ _s, size_t _n, int _flag, size_t _ssize, const wchar_t * __restrict__ _format, va_list _arg)
        __dj_forward(__vswprintf_chk)
        __attribute__((warning("vswprintf called with length bigger than size of buffer")));
int __vswprintf_alias(wchar_t * __restrict__ _s, size_t _n, const wchar_t * __restrict__ _format, va_list _arg)
        __dj_forward(vswprintf);

__dj_fortify_function int
vswprintf(wchar_t * __restrict__ _s, size_t _n, const wchar_t * __restrict__ _format, va_list _arg)
{
  int _flag = 0;
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);

  if ((((__typeof(_n))0 < (__typeof(_n))-1) || (__builtin_constant_p(_n) && _n >= 0)) \
  &&  __builtin_constant_p(_n <= _sz/sizeof(wchar_t))) {
    if (_n <= _sz/sizeof(wchar_t)) {
      if (_flag) {
        return __vswprintf_chk(_s, _n, _flag, _sz/sizeof(wchar_t), _format, _arg);
      } else {
        return __vswprintf_alias(_s, _n, _format, _arg);
      }
    } else {
      return __vswprintf_chk_warn(_s, _n, _flag, _sz/sizeof(wchar_t), _format, _arg);
    }
  } else {
    return __vswprintf_chk(_s, _n, _flag, _sz/sizeof(wchar_t), _format, _arg);
  }
}

wchar_t * __fgetws_chk_warn(wchar_t * __restrict__ _s, int _n, struct __dj_FILE * __restrict__ _stream, size_t _ssize)
        __dj_forward(__fgetws_chk)
        __attribute__((warning("fgetws called with length bigger than size of buffer")));
wchar_t * __fgetws_alias(wchar_t * __restrict__ _s, int _n, struct __dj_FILE * __restrict__ _stream)
        __dj_forward(fgetws);

__dj_fortify_function wchar_t *
fgetws(wchar_t * __restrict__ _s, int _n, struct __dj_FILE * __restrict__ _stream)
{
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(fgets, _n, sizeof(_s[0]), _sz, _s, _n, _stream);
}

wchar_t * __wcscpy_alias(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2)
        __dj_forward(wcscpy);

__dj_fortify_function wchar_t *
wcscpy(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2)
{
  size_t _sz = __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1);
  if (_sz == (size_t)(-1)) {
    return __wcscpy_alias(_s1, _s2);
  } else {
    return __wcscpy_chk(_s1, _s2, _sz);
  }
}

wchar_t * __wcsncpy_chk_warn(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n, size_t _s1size)
        __dj_forward(__wcsncpy_chk)
        __attribute__((warning("wcsncpy called with length bigger than size of buffer")));
wchar_t * __wcsncpy_alias(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n)
        __dj_forward(wcsncpy);

__dj_fortify_function wchar_t *
wcsncpy(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n)
{
  size_t _sz = __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(wcsncpy, _n, sizeof(_s1[0]), _sz, _s1, _s2, _n);
}

wchar_t * __wmemcpy_chk_warn(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n, size_t _s1size)
        __dj_forward(__wmemcpy_chk)
        __attribute__((warning("wmemcpy called with length bigger than size of buffer")));
wchar_t * __wmemcpy_alias(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n)
        __dj_forward(wmemcpy);

__dj_fortify_function wchar_t *
wmemcpy(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n)
{
  size_t _sz = __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(wmemcpy, _n, sizeof(_s1[0]), _sz, _s1, _s2, _n);
}

wchar_t * __wmemmove_chk_warn(wchar_t *_s1, const wchar_t *_s2, size_t _n, size_t _s1size)
        __dj_forward(__wmemmove_chk)
        __attribute__((warning("wmemmove called with length bigger than size of buffer")));
wchar_t * __wmemmove_alias(wchar_t *_s1, const wchar_t *_s2, size_t _n)
        __dj_forward(wmemmove);

__dj_fortify_function wchar_t *
wmemmove(wchar_t *_s1, const wchar_t *_s2, size_t _n)
{
  size_t _sz = __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(wmemmove, _n, sizeof(_s1[0]), _sz, _s1, _s2, _n);
}

wchar_t * __wcscat_alias(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2)
        __dj_forward(wcscat);

__dj_fortify_function wchar_t *
wcscat(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2)
{
  size_t _sz = __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1);
  if (_sz == (size_t)(-1)) {
    return __wcscat_alias(_s1, _s2);
  } else {
    return __wcscat_chk(_s1, _s2, _sz);
  }
}

wchar_t * __wcsncat_chk_warn(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n, size_t _s1size)
        __dj_forward(__wcsncat_chk)
        __attribute__((warning("wcsncat called with length bigger than size of buffer")));
wchar_t * __wcsncat_alias(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n)
        __dj_forward(wcsncat);

__dj_fortify_function wchar_t *
wcsncat(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n)
{
  size_t _sz = __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(wcsncat, _n, sizeof(_s1[0]), _sz, _s1, _s2, _n);
}

size_t __wcsxfrm_chk_warn(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n, size_t _s1size)
        __dj_forward(__wcsxfrm_chk)
        __attribute__((warning("wcsxfrm called with length bigger than size of buffer")));
size_t __wcsxfrm_alias(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n)
        __dj_forward(wcsxfrm);

__dj_fortify_function size_t
wcsxfrm(wchar_t * __restrict__ _s1, const wchar_t * __restrict__ _s2, size_t _n)
{
  size_t _sz = __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(wcsxfrm, _n, sizeof(_s1[0]), _sz, _s1, _s2, _n);
}

wchar_t * __wmemset_chk_warn(wchar_t *_s, wchar_t _c, size_t _n, size_t _ssize)
        __dj_forward(__wmemset_chk)
        __attribute__((warning("wmemset called with length bigger than size of buffer")));
wchar_t * __wmemset_alias(wchar_t *_s, wchar_t _c, size_t _n)
        __dj_forward(wmemset);

__dj_fortify_function wchar_t *
wmemset(wchar_t *_s, wchar_t _c, size_t _n)
{
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(wmemset, _n, sizeof(_s[0]), _sz, _s, _c, _n);
}

size_t __wcsftime_chk_warn(wchar_t * __restrict__ _s, size_t _maxsize, const wchar_t * __restrict__ _format, const struct tm * __restrict__ _timeptr, size_t _ssize)
        __dj_forward(__wcsftime_chk)
        __attribute__((warning("wcsftime called with length bigger than size of buffer")));
size_t __wcsftime_alias(wchar_t * __restrict__ _s, size_t _maxsize, const wchar_t * __restrict__ _format, const struct tm * __restrict__ _timeptr)
        __dj_forward(wcsftime);

__dj_fortify_function size_t
wcsftime(wchar_t * __restrict__ _s, size_t _maxsize, const wchar_t * __restrict__ _format, const struct tm * __restrict__ _timeptr)
{
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(wcsftime, _maxsize, sizeof(_s[0]), _sz, _s, _maxsize, _format, _timeptr);
}

size_t __wcrtomb_chk_warn(char * __restrict__ _s, wchar_t _wc, mbstate_t * __restrict__ _ps, size_t _ssize)
        __dj_forward(__wcrtomb_chk)
        __attribute__((warning("wcrtomb called with buffer smaller than MB_LEN_MAX")));
size_t __wcrtomb_alias(char * __restrict__ _s, wchar_t _wc, mbstate_t * __restrict__ _ps)
        __dj_forward(wcrtomb);

__dj_fortify_function size_t
wcrtomb(char * __restrict__ _s, wchar_t _wc, mbstate_t * __restrict__ _ps)
{
  /* This must be the same as MB_LEN_MAX in limits.h */
  const int __DJ_MB_LEN_MAX = 5;

  if (_s == NULL) {
    return __wcrtomb_alias(_s, _wc, _ps);
  } else {
    size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);
    return __dj_fortify_n(wcrtomb, __DJ_MB_LEN_MAX, sizeof(_s[0]), _sz, _s, _wc, _ps);
  }
}

size_t __mbsrtowcs_chk_warn(wchar_t * __restrict__ _dst, const char ** __restrict__ _src, size_t _len, mbstate_t * __restrict__ _ps, size_t _dstsize)
        __dj_forward(__mbsrtowcs_chk)
        __attribute__((warning("mbsrtowcs called with length bigger than size of buffer")));
size_t __mbsrtowcs_alias(wchar_t * __restrict__ _dst, const char ** __restrict__ _src, size_t _len, mbstate_t * __restrict__ _ps)
        __dj_forward(mbsrtowcs);

__dj_fortify_function size_t
mbsrtowcs(wchar_t * __restrict__ _dst, const char ** __restrict__ _src, size_t _len, mbstate_t * __restrict__ _ps)
{
  if (_dst == NULL) {
    return __mbsrtowcs_alias(_dst, _src, _len, _ps);
  } else {
    size_t _sz = __dj_bos(_dst, __DJ_USE_FORTIFY_LEVEL > 1);
    return __dj_fortify_n(mbsrtowcs, _len, sizeof(_dst[0]), _sz, _dst, _src, _len, _ps);
  }
}

size_t __wcsrtombs_chk_warn(char * __restrict__ _dst, const wchar_t ** __restrict__ _src, size_t _len, mbstate_t * __restrict__ _ps, size_t _dstsize)
        __dj_forward(__wcsrtombs_chk)
        __attribute__((warning("wcsrtombs called with length bigger than size of buffer")));
size_t __wcsrtombs_alias(char * __restrict__ _dst, const wchar_t ** __restrict__ _src, size_t _len, mbstate_t * __restrict__ _ps)
        __dj_forward(wcsrtombs);

__dj_fortify_function size_t
wcsrtombs(char * __restrict__ _dst, const wchar_t ** __restrict__ _src, size_t _len, mbstate_t * __restrict__ _ps)
{
  if (_dst == NULL) {
    return __wcsrtombs_alias(_dst, _src, _len, _ps);
  } else {
    size_t _sz = __dj_bos(_dst, __DJ_USE_FORTIFY_LEVEL > 1);
    return __dj_fortify_n(wcsrtombs, _len, sizeof(_dst[0]), _sz, _dst, _src, _len, _ps);
  }
}

#endif

#if __DJ_USE_FORTIFY_LEVEL > 1
__dj_fortify_function int
wprintf(const wchar_t * __restrict__ _format, ...)
{
  int _flag = (__DJ_USE_FORTIFY_LEVEL > 1) && !__builtin_constant_p(_format);
  return __wprintf_chk(_flag, _format, __builtin_va_arg_pack());
}

__dj_fortify_function int
fwprintf(struct __dj_FILE * __restrict__ _stream, const wchar_t * __restrict__ _format, ...)
{
  int _flag = (__DJ_USE_FORTIFY_LEVEL > 1) && !__builtin_constant_p(_format);
  return __fwprintf_chk(_stream, _flag, _format, __builtin_va_arg_pack());
}

__dj_fortify_function int
vwprintf(const wchar_t * __restrict__ _format, va_list _arg)
{
  int _flag = 0;
  return __vwprintf_chk(_flag, _format, __builtin_va_arg_pack());
}

__dj_fortify_function int
vfwprintf(struct __dj_FILE * __restrict__ _stream, const wchar_t * __restrict__ _format, va_list _arg)
{
  int _flag = 0;
  return __vfwprintf_chk(_stream, _flag, _format, __builtin_va_arg_pack());
}

#endif

#endif /* (__STDC_VERSION__ >= 199901L) || !__STRICT_ANSI__ */

#ifndef __STRICT_ANSI__

int	_dowprnt(const wchar_t *_fmt, va_list _args, struct __dj_FILE *_f);
int	_dowscan(struct __dj_FILE *_f, const wchar_t *_fmt, va_list _args);
int	_dowscan_low(struct __dj_FILE *, wint_t (*)(struct __dj_FILE *_get), wint_t (*_unget)(wint_t, struct __dj_FILE *), const wchar_t *_fmt, va_list _args);
#ifdef __DJ_CHECKED_FUNCTION
int	__dowprnt_chk(const wchar_t *_fmt, va_list _args, struct __dj_FILE *_f, int _flag);
#endif

#ifndef _POSIX_SOURCE

#endif /* !_POSIX_SOURCE */
#endif /* !__STRICT_ANSI__ */
#endif /* !__dj_ENFORCE_ANSI_FREESTANDING */

#ifndef __dj_ENFORCE_FUNCTION_CALLS
#endif /* !__dj_ENFORCE_FUNCTION_CALLS */

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_wchar_h_ */

