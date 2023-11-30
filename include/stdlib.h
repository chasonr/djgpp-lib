/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2014 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2000 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_stdlib_h_
#define __dj_include_stdlib_h_

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

#define EXIT_FAILURE	1
#define EXIT_SUCCESS	0
#define MB_CUR_MAX	__dj_mb_cur_max
#define RAND_MAX	2147483647

extern int __dj_mb_cur_max;

typedef struct {
  int quot;
  int rem;
} div_t;

typedef struct {
  long quot;
  long rem;
} ldiv_t;

#ifndef _SIZE_T
__DJ_size_t
#define _SIZE_T
#endif

#ifndef _WCHAR_T
__DJ_wchar_t
#define _WCHAR_T
#endif

void	abort(void) __attribute__((noreturn));
int	abs(int _i);
int	atexit(void (*_func)(void));
double	atof(const char *_s);
int	atoi(const char *_s);
long	atol(const char *_s);
void *	bsearch(const void *_key, const void *_base, size_t _nelem,
		size_t _size, int (*_cmp)(const void *_ck, const void *_ce));
void *	calloc(size_t _nelem, size_t _size);
div_t	div(int _numer, int _denom);
void	exit(int _status) __attribute__((noreturn));
void	free(void *_ptr);
char *	getenv(const char *_name);
long	labs(long _i);
ldiv_t	ldiv(long _numer, long _denom);
void *	malloc(size_t _size);
int	mblen(const char *_s, size_t _n);
size_t	mbstowcs(wchar_t * __restrict__ _wcs, const char * __restrict__ _s, size_t _n);
int	mbtowc(wchar_t *_pwc, const char *_s, size_t _n);
void	qsort(void *_base, size_t _nelem, size_t _size,
	      int (*_cmp)(const void *_e1, const void *_e2));
int	rand(void);
void *	realloc(void *_ptr, size_t _size);
void	srand(unsigned _seed);
double	strtod(const char *_s, char **_endptr);
long	strtol(const char *_s, char **_endptr, int _base);
unsigned long	strtoul(const char *_s, char **_endptr, int _base);
int	system(const char *_s);
size_t	wcstombs(char * __restrict__ _s, const wchar_t * __restrict__ _wcs, size_t _n);
int	wctomb(char *_s, wchar_t _wchar);


#if __DJ_USE_FORTIFY_LEVEL > 0 || defined(__DJ_CHECKED_FUNCTION)
extern size_t __mbstowcs_chk(wchar_t * __restrict__ _wcs, const char * __restrict__ _s, size_t _n, size_t _wcssize);
extern size_t __wcstombs_chk(char * __restrict__ _s, const wchar_t * __restrict__ _wcs, size_t _n, size_t _ssize);
extern int    __wctomb_chk(char *_s, wchar_t _wchar, size_t _ssize);
#endif


#if __DJ_USE_FORTIFY_LEVEL > 0
size_t __mbstowcs_chk_warn(wchar_t * __restrict__ _wcs, const char * __restrict__ _s, size_t _n, size_t _wcssize)
                __dj_forward(__mbstowcs_chk)
                __attribute__((__warning__("mbstowcs called with buffer size too small")));
size_t __mbstowcs_alias(wchar_t * __restrict__ _wcs, const char * __restrict__ _s, size_t _n)
                __dj_forward(mbstowcs);

__dj_fortify_function size_t
mbstowcs(wchar_t * __restrict__ _wcs, const char * __restrict__ _s, size_t _n)
{
  size_t _sz = __dj_bos(_wcs, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(mbstowcs, _n, sizeof(_wcs[0]), _sz,
                        _wcs, _s, _n);
}

size_t __wcstombs_chk_warn(char * __restrict__ _s, const wchar_t * __restrict__ _wcs, size_t _n, size_t _ssize)
                __dj_forward(__wcstombs_chk)
                __attribute__((__warning__("wcstombs called with buffer size too small")));
size_t __wcstombs_alias(char * __restrict__ _s, const wchar_t * __restrict__ _wcs, size_t _n)
                __dj_forward(wcstombs);

__dj_fortify_function size_t
wcstombs(char * __restrict__ _s, const wchar_t * __restrict__ _wcs, size_t _n)
{
  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(wcstombs, _n, sizeof(_s[0]), _sz,
                        _s, _wcs, _n);
}

int __wctomb_chk_warn(char *_s, wchar_t _wchar, size_t _ssize)
                __dj_forward(__wctomb_chk)
                __attribute__((__warning__("wctomb called with buffer size too small")));
int __wctomb_alias(char *_s, wchar_t _wchar)
                __dj_forward(wctomb);

__dj_fortify_function int
wctomb(char *_s, wchar_t _wchar)
{
  /* This must be the same as MB_LEN_MAX in limits.h */
  const int __DJ_MB_LEN_MAX = 5;

  size_t _sz = __dj_bos(_s, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(wctomb, __DJ_MB_LEN_MAX, sizeof(_s[0]), _sz,
                        _s, _wchar);
}

#endif

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) \
  || !defined(__STRICT_ANSI__) || defined(__cplusplus)

typedef struct {
  long long int quot;
  long long int rem;
} lldiv_t;

void		_Exit(int _status) __attribute__((noreturn));
long long int	atoll(const char *_s);
long long int	llabs(long long int _i);
lldiv_t		lldiv(long long int _numer, long long int _denom);
float		strtof(const char *_s, char **_endptr);
long double	strtold(const char *_s, char **_endptr);
long long int	strtoll(const char *_s, char **_endptr, int _base);
unsigned long long int	strtoull(const char *_s, char **_endptr, int _base);

void quick_exit(int _status) __attribute__((noreturn));
int	at_quick_exit(void (*_func)(void));

void *aligned_alloc(size_t _align, size_t _size);

#endif /* (__STDC_VERSION__ >= 199901L) || !__STRICT_ANSI__ */

#ifndef __STRICT_ANSI__

long	a64l(const char *_string);
char *	l64a(long _value);
char *	mktemp(char *_template);
char *	mkdtemp(char *_template);
int	mkstemp(char *_template);
int	putenv(char *_val);
char *	realpath(const char *_path, char *_resolved);
int	setenv(const char *_var, const char *_val, int _overwrite);
int	unsetenv(const char *_var);

#if __DJ_USE_FORTIFY_LEVEL > 0 || defined(__DJ_CHECKED_FUNCTION)
extern char *__realpath_chk(const char *_path, char *_resolved, size_t _resolvedlen);
#endif

#if __DJ_USE_FORTIFY_LEVEL > 0
__dj_fortify_function char *
realpath(const char *_path, char *_resolved)
{
  size_t _sz = __dj_bos(_resolved, __DJ_USE_FORTIFY_LEVEL > 1);
  return __realpath_chk(_path, _resolved, _sz);
}
#endif

#ifndef _POSIX_SOURCE

void *		alloca(size_t _size);
long double	_atold(const char *_s);
void		cfree(void *_ptr);
double          drand48(void);
char *		ecvtbuf(double _val, int _nd, int *_dp, int *_sn, char *_bf);
char *		ecvt(double _val, int _nd, int *_dp, int *_sn);
double          erand48(unsigned short _state[3]);
char *		fcvtbuf(double _val, int _nd, int *_dp, int *_sn, char *_bf);
char *		fcvt(double _val, int _nd, int *_dp, int *_sn);
char *		gcvt(double _val, int _nd, char *_buf);
char *		getpass(const char *_prompt);
int		getlongpass(const char *_prompt, char *_buffer, int _max_len);
char *		itoa(int _value, char *_buffer, int _radix);
long            jrand48(unsigned short _state[3]);
void            lcong48(unsigned short _param[7]);
unsigned long   lrand48(void);
long            mrand48(void);
unsigned long   nrand48(unsigned short _state[3]);
unsigned short *seed48(unsigned short _state_seed[3]);
void            srand48(long _seedval);
int		stackavail(void);
long double	_strtold(const char *_s, char **_endptr);
void		swab(const void *_from, void *_to, int _nbytes);
void *		valloc (size_t _amt);

#ifndef alloca
#define alloca __builtin_alloca
#endif

/* BSD Random Number Generator */
char  *	initstate (unsigned _seed, char *_arg_state, int _n);
char  *	setstate(char *_arg_state);
long	random(void);
int	srandom(int _seed);

/* These vary in expected prototype, so we just don't prototype them.
void		xfree(void *_ptr);
void *		xmalloc(size_t _size);
void *		xrealloc(void *ptr, size_t _size);
*/

#define __system_redirect	      0x0001 /* redirect internally */
#define __system_call_cmdproc	      0x0002 /* always call COMMAND/$SHELL */
#define __system_use_shell	      0x0004 /* use $SHELL if set */
#define __system_allow_multiple_cmds  0x0008 /* allow `cmd1; cmd2; ...' */
#define __system_allow_long_cmds      0x0010 /* handle commands > 126 chars  */
#define __system_emulate_command      0x0020 /* try to emulate the shell */
#define __system_handle_null_commands 0x1000 /* ignore cmds with no effect */
#define __system_ignore_chdir	      0x2000 /* make `cd' be a null command */
#define __system_emulate_chdir	      0x4000 /* handle `cd' internally */

extern int __system_flags;

#endif /* !_POSIX_SOURCE */
#endif /* !__STRICT_ANSI__ */
#endif /* !__dj_ENFORCE_ANSI_FREESTANDING */

#ifndef __dj_ENFORCE_FUNCTION_CALLS
#endif /* !__dj_ENFORCE_FUNCTION_CALLS */

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_stdlib_h_ */
