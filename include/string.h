/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2000 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_string_h_
#define __dj_include_string_h_

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

void *	memchr(const void *_s, int _c, size_t _n);
int	memcmp(const void *_s1, const void *_s2, size_t _n);
void *	memcpy(void * __restrict__ _dest, const void * __restrict__ _src, size_t _n);
void *	memmove(void *_s1, const void *_s2, size_t _n);
void *	memset(void *_s, int _c, size_t _n);
char *	strcat(char * __restrict__ _s1, const char * __restrict__ _s2);
char *	strchr(const char *_s, int _c);
int	strcmp(const char *_s1, const char *_s2);
int	strcoll(const char *_s1, const char *_s2);
char *	strcpy(char * __restrict__ _s1, const char * __restrict__ _s2);
size_t	strcspn(const char *_s1, const char *_s2);
char *	strerror(int _errcode);
size_t	strlen(const char *_s);
char *	strncat(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n);
int	strncmp(const char *_s1, const char *_s2, size_t _n);
char *	strncpy(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n);
char *	strpbrk(const char *_s1, const char *_s2);
char *	strrchr(const char *_s, int _c);
size_t	strspn(const char *_s1, const char *_s2);
char *	strstr(const char *_s1, const char *_s2);
char *	strtok(char *  _s1, const char *  _s2);
size_t	strxfrm(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n);

#if __DJ_USE_FORTIFY_LEVEL > 0 || defined(__DJ_CHECKED_FUNCTION)
extern void *__memcpy_chk(void * __restrict__ _s1, const void * __restrict__ _s2, size_t _n, size_t _s1size);
extern void *__memmove_chk(void * __restrict__ _s1, const void * __restrict__ _s2, size_t _n, size_t _s1size);
extern void *__memset_chk(void *_s, int _c, size_t _n, size_t _ssize);
extern char *__strcat_chk(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _s1size);
extern char *__strcpy_chk(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _s1size);
extern char *__strncat_chk(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n, size_t _s1size);
extern char *__strncpy_chk(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n, size_t _s1size);
extern size_t __strxfrm_chk(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n, size_t _s1size);
#endif

#if __DJ_USE_FORTIFY_LEVEL > 0

__dj_fortify_function void *
memcpy(void * __restrict__ _dest, const void * __restrict__  _src, size_t _n)
{
  return __builtin___memcpy_chk(_dest, _src, _n, __dj_bos(_dest, 0));
}

__dj_fortify_function void *
memmove(void *_dest, const void * _src, size_t _n)
{
  return __builtin___memmove_chk(_dest, _src, _n, __dj_bos(_dest, 0));
}

__dj_fortify_function void *
memset(void *_s, int _c, size_t _n)
{
  return __builtin___memset_chk(_s, _c, _n, __dj_bos(_s, 0));
}

__dj_fortify_function char *
strcat(char * __restrict__ _s1, const char * __restrict__ _s2)
{
  return __builtin___strcat_chk(_s1, _s2,
                                __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1));
}

__dj_fortify_function char *
strcpy(char * __restrict__ _s1, const char * __restrict__ _s2)
{
  return __builtin___strcpy_chk(_s1, _s2,
                                __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1));
}

__dj_fortify_function char *
strncat(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n)
{
  return __builtin___strncat_chk(_s1, _s2, _n,
                                 __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1));
}

__dj_fortify_function char *
strncpy(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n)
{
  return __builtin___strncpy_chk(_s1, _s2, _n,
                                 __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1));
}

extern size_t __strxfrm_chk_warn(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n, size_t _s1size)
        __dj_forward(__strxfrm_chk)
        __attribute__((__warning__("strxfrm called with length bigger than size of destination buffer")));
extern size_t __strxfrm_alias(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n)
        __dj_forward(strxfrm);

__dj_fortify_function size_t
strxfrm(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n)
{
  size_t _sz = __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(strxfrm, _n, sizeof(_s1[0]), _sz,
            _s1, _s2, _n);
}

#endif

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) \
  || !defined(__STRICT_ANSI__) || defined(__cplusplus)

#endif /* (__STDC_VERSION__ >= 199901L) || !__STRICT_ANSI__ */

#ifndef __STRICT_ANSI__

int	strerror_r(int _errnum, char *_strerrbuf, size_t _buflen);
char *	strtok_r(char *  _s1, const char *  _s2, char ** _s3);

#ifndef _POSIX_SOURCE

#include <sys/movedata.h>

int	bcmp(const void *_ptr1, const void *_ptr2, int _length);
void 	bcopy(const void *_a, void *_b, size_t _len);
void 	bzero(void *_ptr, size_t _len);
int	ffs(int _mask);
char *  index(const char *_string, int _c);
void *	memccpy(void * __restrict__ _to, const void * __restrict__ _from, int _c, size_t _n);
int	memicmp(const void *_s1, const void *_s2, size_t _n);
char *  rindex(const char *_string, int _c);
char *	stpcpy(char * __restrict__ _dest, const char * __restrict__ _src);
char *	stpncpy(char * __restrict__ _dest, const char * __restrict__ _src, size_t _n);
char *	strdup(const char *_s);
char *	strndup(const char *_s, size_t _n);
size_t	strlcat(char * __restrict__ _dest, const char * __restrict__ _src, size_t _size);
size_t	strlcpy(char * __restrict__ _dest, const char * __restrict__ _src, size_t _size);
char *	strlwr(char *_s);
int	strcasecmp(const char *_s1, const char *_s2);
int	stricmp(const char *_s1, const char *_s2);
int	strncasecmp(const char *_s1, const char *_s2, size_t _n);
int	strnicmp(const char *_s1, const char *_s2, size_t _n);
size_t	strnlen(const char *_s, size_t _n);
char *	strsep(char **_stringp, const char *_delim);
char *	strupr(char *_s);

#if __DJ_USE_FORTIFY_LEVEL > 0 || defined(__DJ_CHECKED_FUNCTION)
extern char *__stpcpy_chk(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _s1size);
extern char *__stpncpy_chk(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n, size_t _s1size);
extern void *__memccpy_chk(void * __restrict__ _to, const void * __restrict__ _from, int _c, size_t _n, size_t _tosize);
extern size_t __strlcat_chk(char * __restrict__ _dest, const char * __restrict__ _src, size_t _size, size_t _destsize);
extern size_t __strlcpy_chk(char * __restrict__ _dest, const char * __restrict__ _src, size_t _size, size_t _destsize);
#endif

#if __DJ_USE_FORTIFY_LEVEL > 0

__dj_fortify_function void
bcopy(const void *_a, void *_b, size_t _len)
{
  __builtin___memmove_chk(_b, _a, _len, __dj_bos(_b, 0));
}

__dj_fortify_function void
bzero(void *_ptr, size_t _len)
{
  __builtin___memset_chk(_ptr, '\0', _len, __dj_bos(_ptr, 0));
}

__dj_fortify_function char *
stpcpy(char * __restrict__ _s1, const char * __restrict__ _s2)
{
  return __builtin___stpcpy_chk(_s1, _s2,
                                __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1));
}

__dj_fortify_function char *
stpncpy(char * __restrict__ _s1, const char * __restrict__ _s2, size_t _n)
{
  return __builtin___stpncpy_chk(_s1, _s2, _n,
                                 __dj_bos(_s1, __DJ_USE_FORTIFY_LEVEL > 1));
}

extern void *__memccpy_chk_warn(void * __restrict__ _to, const void * __restrict__ _from, int _c, size_t _n, size_t _tosize)
        __dj_forward(__memccpy_chk)
        __attribute__((__warning__("memccpy called with length bigger than size of destination buffer")));
extern void *__memccpy_alias(void * __restrict__ _to, const void * __restrict__ _from, int _c, size_t _n)
        __dj_forward(memccpy);

__dj_fortify_function void *
memccpy(void * __restrict__ _to, const void * __restrict__ _from, int _c, size_t _n)
{
  size_t _sz = __dj_bos(_to, 0);
  return __dj_fortify_n(memccpy, _n, sizeof(_to[0]), _sz,
            _to, _from, _c, _n);
}

extern size_t __strlcat_chk_warn(char * __restrict__ _dest, const char * __restrict__ _src, size_t _size, size_t _destsize)
        __dj_forward(__strlcat_chk)
        __attribute__((__warning__("strlcat called with length bigger than size of destination buffer")));
extern size_t __strlcat_chk(char * __restrict__ _dest, const char * __restrict__ _src, size_t _size, size_t _destsize)
        __dj_forward(strlcat);

__dj_fortify_function size_t
strlcat(char * __restrict__ _dest, const char * __restrict__ _src, size_t _size)
{
  size_t _sz = __dj_bos(_dest, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(strlcat, _size, sizeof(_dest[0]), _sz,
            _dest, _src, _size);
}

extern size_t __strlcpy_chk_warn(char * __restrict__ _dest, const char * __restrict__ _src, size_t _size, size_t _destsize)
        __dj_forward(__strlcpy_chk)
        __attribute__((__warning__("strlcpy called with length bigger than size of destination buffer")));
extern size_t __strlcpy_chk(char * __restrict__ _dest, const char * __restrict__ _src, size_t _size, size_t _destsize)
        __dj_forward(strlcpy);

__dj_fortify_function size_t
strlcpy(char * __restrict__ _dest, const char * __restrict__ _src, size_t _size)
{
  size_t _sz = __dj_bos(_dest, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(strlcpy, _size, sizeof(_dest[0]), _sz,
            _dest, _src, _size);
}

#endif

#endif /* !_POSIX_SOURCE */
#endif /* !__STRICT_ANSI__ */
#endif /* !__dj_ENFORCE_ANSI_FREESTANDING */

#ifndef __dj_ENFORCE_FUNCTION_CALLS
#endif /* !__dj_ENFORCE_FUNCTION_CALLS */

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_string_h_ */
