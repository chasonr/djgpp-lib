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
#define _MBSTATE_T
typedef struct
{
  int shift_state;
} mbstate_t;
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

#endif /* (__STDC_VERSION__ >= 199901L) || !__STRICT_ANSI__ */

#ifndef __STRICT_ANSI__

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

