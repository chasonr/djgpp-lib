/* Copyright (C) 2012 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2000 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_unistd_h_
#define __dj_include_unistd_h_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __dj_ENFORCE_ANSI_FREESTANDING

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) \
  || !defined(__STRICT_ANSI__) || defined(__cplusplus)

#endif /* (__STDC_VERSION__ >= 199901L) || !__STRICT_ANSI__ */

#ifndef __STRICT_ANSI__

#include <sys/types.h> /* NOT POSIX but you can't include just unistd.h without it */
#include <sys/djtypes.h>
#include <sys/fortify.h>
#include <sys/attrib.h>

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

/* `lockf' is a simpler interface to the locking facilities of `fcntl'.
   LEN is always relative to the current file position.
   The CMD argument is one of the following.  */

# define F_ULOCK 0     /* Unlock a previously locked region.  */
# define F_LOCK  1     /* Lock a region for exclusive use.  */
# define F_TLOCK 2     /* Test and lock a region for exclusive use.  */
# define F_TEST  3     /* Test a region for other processes locks.  */

/* Some programs think they know better... */
#undef NULL
#if (__GNUC__ >= 4) && defined(__cplusplus)
#  define NULL          __null
#elif defined(__cplusplus)
#  define NULL          0
#else
#  define NULL          ((void*)0)
#endif

#define F_OK	0x01
#define R_OK	0x02
#define W_OK	0x04
#define X_OK	0x08

#define STDIN_FILENO		0
#define STDOUT_FILENO		1
#define STDERR_FILENO		2

#define _CS_PATH				1
#define _CS_POSIX_V6_ILP32_OFF32_CFLAGS		2
#define _CS_POSIX_V6_ILP32_OFF32_LDFLAGS	3
#define _CS_POSIX_V6_ILP32_OFF32_LIBS		4

#define _PC_CHOWN_RESTRICTED	1
#define _PC_LINK_MAX		2
#define _PC_MAX_CANON		3
#define _PC_MAX_INPUT		4
#define _PC_NAME_MAX		5
#define _PC_NO_TRUNC		6
#define _PC_PATH_MAX		7
#define _PC_PIPE_BUF		8
#define _PC_VDISABLE		9

#define _POSIX_CHOWN_RESTRICTED	0
#undef  _POSIX_JOB_CONTROL
#define _POSIX_NO_TRUNC		0
#undef  _POSIX_SAVED_IDS
#define _POSIX_VDISABLE		-1
#define _POSIX_VERSION		199009L
#define _POSIX_V6_ILP32_OFF32	1

#define _SC_ARG_MAX		1
#define _SC_CHILD_MAX		2
#define _SC_CLK_TCK		3
#define _SC_JOB_CONTROL		4
#define _SC_NGROUPS_MAX		5
#define _SC_OPEN_MAX		6
#define _SC_SAVED_IDS		7
#define _SC_STREAM_MAX		8
#define _SC_TZNAME_MAX		9
#define _SC_VERSION		10
#define _SC_V6_ILP32_OFF32	11

#ifndef _SIZE_T
__DJ_size_t
#define _SIZE_T
#endif
#ifndef _SSIZE_T
__DJ_ssize_t
#define _SSIZE_T
#endif

extern char *optarg;
extern int optind, opterr, optopt;

void		__exit(int _status) __attribute__((noreturn));
void		_exit(int _status) __attribute__((noreturn));
int		access(const char *_path, int _amode);
unsigned int	alarm(unsigned int _seconds);
int		chdir(const char *_path);
int		chown(const char *_path, uid_t _owner, gid_t _group);
int		close(int _fildes);
size_t		confstr(int _name, char *_buf, size_t _len);
char *		ctermid(char *_s);
int		dup(int _fildes);
int		dup2(int _fildes, int _fildes2);
int		execl(const char *_path, const char *_arg, ...);
int		execle(const char *_path, const char *_arg, ...);
int		execlp(const char *_file, const char *_arg, ...);
int		execv(const char *_path, char *const _argv[]);
int		execve(const char *_path, char *const _argv[], char *const _envp[]);
int		execvp(const char *_file, char *const _argv[]);
int		fchdir(int _fd);
pid_t		fork(void);
long		fpathconf(int _fildes, int _name);
char *		getcwd(char *_buf, size_t _size);
gid_t		getegid(void);
uid_t		geteuid(void);
gid_t		getgid(void);
int		getgroups(int _gidsetsize, gid_t *_grouplist);
char *		getlogin(void);
int		getopt(int _argc, char *const _argv[], const char *_optstring);
pid_t		getpgrp(void);
pid_t		getpid(void);
pid_t		getppid(void);
uid_t		getuid(void);
int		isatty(int _fildes);
int		link(const char *_existing, const char *_new);
off_t		lseek(int _fildes, off_t _offset, int _whence);
long		pathconf(const char *_path, int _name);
int		pause(void);
int		pipe(int _fildes[2]);
ssize_t		pwrite(int _fildes, const void *_buf, size_t _nbyte, off_t _offset);
ssize_t		read(int _fildes, void *_buf, size_t _nbyte);
int		rmdir(const char *_path);
int		setgid(gid_t _gid);
int		setpgid(pid_t _pid, pid_t _pgid);
pid_t		setsid(void);
int		setuid(uid_t uid);
unsigned int	sleep(unsigned int _seconds);
long		sysconf(int _name);
pid_t		tcgetpgrp(int _fildes);
int		tcsetpgrp(int _fildes, pid_t _pgrp_id);
char *		ttyname(int _fildes);
int		unlink(const char *_path);
ssize_t		write(int _fildes, const void *_buf, size_t _nbyte);

#if __DJ_USE_FORTIFY_LEVEL > 0 || defined(__DJ_CHECKED_FUNCTION)
extern size_t  __confstr_chk(int _name, char *_buf, size_t _len, size_t _bufsize);
extern char *  __getcwd_chk(char *_buf, size_t _size, size_t _bufsize);
extern int     __getgroups_chk(int _gidsetsize, gid_t *_grouplist, size_t _grouplistsize);
extern ssize_t __read_chk(int _fildes, void *_buf, size_t _nbyte, size_t _bufsize);
#endif

#if __DJ_USE_FORTIFY_LEVEL > 0

size_t  __confstr_chk_warn(int _name, char *_buf, size_t _len, size_t _bufsize)
                __dj_forward(__confstr_chk)
                __attribute__((__warning__("confstr called with buffer size too small")));
size_t  __confstr_alias(int _name, char *_buf, size_t _len)
                __dj_forward(confstr);

__dj_fortify_function size_t
confstr(int _name, char *_buf, size_t _len)
{
  size_t _sz = __dj_bos(_buf, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(confstr, _len, sizeof(_buf[0]), _sz,
                        _name, _buf, _len);
}

char *__getcwd_chk_warn(char *_buf, size_t _size, size_t _bufsize)
                __dj_forward(__getcwd_chk)
                __attribute__((__warning__("getcwd called with buffer size too small")));
char *__getcwd_alias(char *_buf, size_t _size)
                __dj_forward(getcwd);

__dj_fortify_function char *
getcwd(char *_buf, size_t _size)
{
  size_t _sz = __dj_bos(_buf, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(getcwd, _size, sizeof(_buf[0]), _sz,
                        _buf, _size);
}

int __getgroups_chk_warn(int _gidsetsize, gid_t *_grouplist, size_t _grouplistsize)
                __dj_forward(__getgroups_chk)
                __attribute__((__warning__("getgroups called with buffer size too small")));
int __getgroups_alias(int _gidsetsize, gid_t *_grouplist)
                __dj_forward(getgroups);

__dj_fortify_function int
getgroups(int _gidsetsize, gid_t *_grouplist)
{
  size_t _sz = __dj_bos(_grouplist, 0);
  return __dj_fortify_n(getgroups, _gidsetsize, sizeof(_grouplist[0]), _sz,
                        _gidsetsize, _grouplist);
}

ssize_t __read_chk_warn(int _fildes, void *_buf, size_t _nbyte, size_t _bufsize)
                __dj_forward(__read_chk)
                __attribute__((__warning__("read called with buffer size too small")));
ssize_t __read_alias(int _fildes, void *_buf, size_t _nbyte)
                __dj_forward(read);

__dj_fortify_function ssize_t
read(int _fildes, void *_buf, size_t _nbyte)
{
  size_t _sz = __dj_bos(_buf, 0);
  return __dj_fortify_n(read, _nbyte, 1, _sz,
                        _fildes, _buf, _nbyte);
}

#endif

#ifndef _POSIX_SOURCE

/* additional access() checks */
#define D_OK	0x10

char *		basename(const char *_fn);
int		brk(void *_heaptop);
char *		dirname(const char *_fn);
int		__file_exists(const char *_fn);
int             fchown(int fd, uid_t owner, gid_t group);
int		fsync(int _fd);
int		ftruncate(int, off_t);
int		getdtablesize(void);
int		gethostname(char *_buf, int _size);
int		getpagesize(void);
#ifndef __DJ_CHECKED_FUNCTION
        __dj_attr_deprecated("the getwd function is dangerous and should not be used")
#endif
char *		getwd(char *__buffer);
int             lchown(const char * file, int owner, int group);
int		lockf(int _fildes, int _cmd, off_t _len);
int		llockf(int _fildes, int _cmd, offset_t _len);
offset_t	llseek(int _fildes, offset_t _offset, int _whence);
int		nice(int _increment);
int             readlink(const char * __file, char * __buffer, size_t __size);
void *		sbrk(int _delta);
int		symlink (const char *, const char *);
int		sync(void);
int		truncate(const char*, off_t);
unsigned int	usleep(unsigned int _useconds);
#ifndef vfork
pid_t		vfork(void);
#endif

#if __DJ_USE_FORTIFY_LEVEL > 0 || defined(__DJ_CHECKED_FUNCTION)
extern int   __gethostname_chk(char *_buf, int _size, size_t _bufsize);
extern char *__getwd_chk(char *__buffer, size_t __buffersize);
extern int   __readlink_chk(const char * __file, char * __buffer, size_t __size, size_t __buffersize);
#endif

#if __DJ_USE_FORTIFY_LEVEL > 0

int   __gethostname_chk_warn(char *_buf, int _size, size_t _bufsize)
                __dj_forward(__gethostname_chk)
                __attribute__((__warning__("gethostname called with buffer size too small")));
int   __gethostname_alias(char *buf, int size)
                __dj_forward(gethostname);

__dj_fortify_function int
gethostname(char *_buf, int _size)
{
  size_t _sz = __dj_bos(_buf, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(gethostname, _size, sizeof(_buf[0]), _sz,
                        _buf, _size);
}

__dj_fortify_function char *
getwd(char *__buffer)
{
  size_t _sz = __dj_bos(__buffer, __DJ_USE_FORTIFY_LEVEL > 1);
  return __getwd_chk(__buffer, _sz);
}

int   __readlink_chk_warn(const char * __file, char * __buffer, size_t __size, size_t __buffersize)
                __dj_forward(__readlink_chk)
                __attribute__((__warning__("readlink called with buffer size too small")));
int   __readlink_alias(const char * __file, char * __buffer, size_t __size)
                __dj_forward(readlink);

__dj_fortify_function int
readlink(const char * __file, char * __buffer, size_t __size)
{
  size_t _sz = __dj_bos(__buffer, __DJ_USE_FORTIFY_LEVEL > 1);
  return __dj_fortify_n(readlink, __size, sizeof(__buffer[0]), _sz,
                        __file, __buffer, __size);
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

#endif /* !__dj_include_unistd_h_ */
