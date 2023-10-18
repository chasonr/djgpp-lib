/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2012 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <locale.h>
#include <stddef.h>
#include <errno.h>
#include <limits.h>
#include <libc/file.h>
#include <libc/local.h>

typedef enum {
  false = 0, true = 1
} bool;

typedef struct char_range {
  wchar_t first;
  wchar_t last;
} char_range;

typedef struct char_set {
  bool invert;
  size_t num_ranges;
  /* size of 2 holds the number of ranges in the set of space characters,
     0x08-0x0D and 0x20 */
  char_range range[2];
} char_set;

#define SPC               01
#define STP               02

#define CHAR              0
#define SHORT             1
#define REGULAR           2
#define LONG              4
#define LONGDOUBLE        8

#define INT               0
#define FLOAT             1

#define DEFAULT_WIDTH     30000
#define BUFFER_INCREMENT  128

static int _innum(int *ptr, int type, int len, int size, FILE *iop,
                  int (*scan_getc)(FILE *), int (*scan_ungetc)(int, FILE *),
                  int *eofptr, const bool allocate_char_buffer,
                  const char_set *cset);
static int _instr(char *ptr, int type, int len, FILE *iop,
                  int (*scan_getc)(FILE *), int (*scan_ungetc)(int, FILE *),
                  int *eofptr, const bool allocate_char_buffer,
                  const char_set *cset);
static int _inwstr(wchar_t *ptr, int type, int len, FILE *iop,
                   int (*scan_getc)(FILE *), int (*scan_ungetc)(int, FILE *),
                   int *eofptr, const bool allocate_char_buffer,
                   const char_set *cset);
static char_set *_getccl(const char **pfmt, int len);
static bool in_charset(const char_set *cset, wchar_t chr);

static const char_set no_chars = {
  false, 0,
  {
    { 0x00, 0x00 },
    { 0x00, 0x00 }
  }
};

static const char_set all_chars = {
  true, 0,
  {
    { 0x00, 0x00 },
    { 0x00, 0x00 }
  }
};

static const char_set spaces = {
  false, 2,
  {
    { 0x09, 0x0D },
    { 0x20, 0x20 }
  }
};

static const char_set nonspaces = {
  true, 2,
  {
    { 0x09, 0x0D },
    { 0x20, 0x20 }
  }
};

static char _sctab[256] = {
  0,0,0,0,0,0,0,0,
  0,SPC,SPC,SPC,SPC,SPC,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  SPC,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
};

static int nchars = 0;
static char decimal_point = '.';

int
_doscan(FILE *iop, const char *fmt, va_list argp)
{
  return(_doscan_low(iop, fgetc, ungetc, fmt, argp));
}

int
_doscan_low(FILE *iop, int (*scan_getc)(FILE *), int (*scan_ungetc)(int, FILE *), const char *fmt, va_list argp)
{
  register int ch;
  int nmatch, n, len, ch1;
  int *ptr, fileended, size;
  int suppressed;
  bool allocate_char_buffer;
  int previous_errno = errno;
  const va_list arg_list = argp;
  bool retrieve_arg_ptr;
  char_set *cset;
  bool ok;

  decimal_point = localeconv()->decimal_point[0];
  nchars = 0;
  nmatch = 0;
  fileended = 0;
  suppressed = 0;
  errno = 0;

  for (;;)
  {
    switch (ch = *fmt++)
    {
    case '\0':
      return nmatch;
    case '%':
      if ((ch = *fmt++) == '%')
        goto def;

      retrieve_arg_ptr = true;
      allocate_char_buffer = false;
      ptr = NULL;
      cset = NULL;
repeat:
      if (ch != '*' && retrieve_arg_ptr)
        ptr = va_arg(argp, int *);
      else
        ch = *fmt++;
      n = len = 0;
      size = REGULAR;
      while (isdigit(ch & 0xff))
      {
        n = n * 10 + ch - '0';
        ch = *fmt++;
      }
      if (ch == '$')
      {
        /* C99 */
        /* for %n$ numeric conversion specifier */
        int i;
        for (argp = arg_list, i = 0; i < n; i++)
          ptr = va_arg(argp, int *);
        retrieve_arg_ptr = false;
        goto repeat;
      }
      else
        len = (n == 0) ? DEFAULT_WIDTH : n;

      if (ch == 'l')
      {
        size = LONG;
        ch = *fmt++;
        if (ch == 'l')
        {
          size = LONGDOUBLE; /* for long long and long double 'll' format */
          ch = *fmt++;
        }
      }
      else if (ch == 'h')
      {
        size = SHORT;
        ch = *fmt++;
        if (ch == 'h')
        {
          /* C99 */
          /* for 'hh' - char */
          size = CHAR;
          ch = *fmt++;
        }
      }
      else if (ch == 'L')
      {
        size = LONGDOUBLE;
        ch = *fmt++;
      }
      else if (ch == 'j')
      {
        /* C99 */
        size = LONGDOUBLE; /* for long long */
        ch = *fmt++;
      }
      else if (ch == 'z')
      {
        /* C99 */
        size = LONG;
        ch = *fmt++;
      }
      else if (ch == 't')
      {
        /* C99 */
        size = REGULAR;
        ch = *fmt++;
      }
      else if (ch == 'm')
      {
        /* POSIX.1 and GNU glibc extension */
        allocate_char_buffer = true;
        ch = *fmt++;
        if (ch == 'l')
        {
          size = LONG;
          ch = *fmt++;
        }
      }
      if (ch == '[')
      {
        cset = _getccl(&fmt, size);
        if (cset == NULL)
          return EOF;
      }

      if (isupper(ch & 0xff))
      {
        /* ch = tolower(ch);
           gcc gives warning: ANSI C forbids braced
           groups within expressions */
        ch += 'a' - 'A';
        /* The following if clause is an extension of ANSI/Posix spec: it
           allows to use %D, %U, %I etc. to store value in a long (rather
           than an int) and %lD, %lU etc. to store value in a long long.
           This extension is supported by some compilers (e.g. Borland C).
           Old pre-ANSI compilers, such as Turbo C 2.0, also interpreted
           %E, %F and %G to store in a double (rather than a float), but
           this contradicts the ANSI Standard, so we don't support it.
           %X should be treated as per the ANSI Standard - no length
           is implied by the upper-case x. */
        if (ch == 'd' || ch == 'i' || ch == 'o' || ch == 'u')
        {
          if (size == LONG)
            size = LONGDOUBLE;
          else if (size != LONGDOUBLE)
            size = LONG;
        }
      }
      if (ch == '\0')
        return EOF;

      if (ch == 'n')
      {
        if (!ptr)
          break;
        if (size == LONG)
          *(long *)ptr = nchars;
        else if (size == CHAR)
          *(char *)ptr = nchars;
        else if (size == SHORT)
          *(short *)ptr = nchars;
        else if (size == LONGDOUBLE)
          *(long long *)ptr = nchars;
        else
          *(int *)ptr = nchars;
        break;
      }

      ok = _innum(ptr, ch, len, size, iop, scan_getc, scan_ungetc, &fileended, allocate_char_buffer, cset);
      free(cset);
      if (ok)
      {
        if (ptr)
          nmatch++;
        else
          suppressed = 1;
      }
      else
      {
        if ((fileended && !nmatch && !suppressed) || (allocate_char_buffer && errno == ENOMEM))
          return EOF;

        errno = previous_errno;
        return nmatch;
      }
      break;
    case ' ':
    case '\n':
    case '\t':
    case '\r':
    case '\f':
    case '\v':
      while (((nchars++, ch1 = scan_getc(iop)) != EOF) && (_sctab[ch1 & 0xff] & SPC))
        ;

      if (ch1 != EOF)
        scan_ungetc(ch1, iop);

      nchars--;
      break;

    default:
def:
      ch1 = scan_getc(iop);
      if (ch1 != EOF) nchars++;
      if (ch1 != ch)
      {
        if (ch1 == EOF)
          return (nmatch || suppressed ? nmatch : EOF);
        scan_ungetc(ch1, iop);
        nchars--;
        return nmatch;
      }
    }
  }
}

static int
_innum(int *ptr, int type, int len, int size, FILE *iop,
       int (*scan_getc)(FILE *), int (*scan_ungetc)(int, FILE *),
       int *eofptr, const bool allocate_char_buffer,
       const char_set *cset)
{
  register char *np;
  char numbuf[64];
  register int c, base;
  int expseen, scale, negflg, c1, ndigit;
  long long lcval;
  int cpos;

  if (type == 'c' || type == 's' || type == '[')
  {
    if (size == LONG)
      return (_inwstr(ptr ? (wchar_t *)ptr : (wchar_t *)NULL, type, len,
                      iop, scan_getc, scan_ungetc, eofptr, allocate_char_buffer,
                      cset));
    else
      return (_instr(ptr ? (char *)ptr : (char *)NULL, type, len,
                     iop, scan_getc, scan_ungetc, eofptr, allocate_char_buffer,
                     cset));
  }
  lcval = 0;
  ndigit = 0;
  scale = INT;
  if (type == 'a' || type == 'e' || type == 'f' || type == 'g')
    scale = FLOAT;
  base = 10;
  if (type == 'o')
    base = 8;
  else if (type == 'x' || type == 'p' || type == 'a')
    base = 16;
  np = numbuf;

  expseen = 0;
  negflg = 0;
  while (((nchars++, c = scan_getc(iop)) != EOF) && (_sctab[c & 0xff] & SPC))
    ;
  if (c == EOF) nchars--;
  if (c == '-')
  {
    negflg++;
    *np++ = c;
    c = scan_getc(iop);
    nchars++;
    len--;
  }
  else if (c == '+')
  {
    len--;
    c = scan_getc(iop);
    nchars++;
  }

  cpos = 0;
  for (; --len >= 0; *np++ = c, c = scan_getc(iop), nchars++)
  {
    cpos++;
    if (c == '0' && cpos == 1 && type == 'i')
      base = 8;
    if ((c == 'x' || c == 'X') && (type == 'a' || type == 'i' || type == 'x')
        && cpos == 2 && lcval == 0)
    {
      base = 16;
      continue;
    }
    if ((c != EOF && isdigit(c & 0xff)  && c - '0' < base)
        || (base == 16 && (('a' <= c && c <= 'f') || ('A' <= c && c <= 'F'))))
    {
      ndigit++;
      if (base == 8)
        lcval <<= 3;
      else if (base == 10)
        lcval = ((lcval << 2) + lcval) << 1;
      else
        lcval <<= 4;
      c1 = c;
      if (isdigit(c & 0xff))
        c -= '0';
      else if ('a' <= c && c <= 'f')
        c -= 'a' - 10;
      else
        c -= 'A' - 10;
      lcval += c;
      c = c1;
      continue;
    }
    else if (c == decimal_point)
    {
      if (scale == INT || base == 8)
        break;
      ndigit++;
      continue;
    }
    else if ((c == 'e' || c == 'E') && expseen == 0)
    {
      if (scale == INT || base == 8 || ndigit == 0)
        break;
      expseen++;
      *np++ = c;
      c = scan_getc(iop);
      nchars++;
      if (c != '+' && c != '-' && ('0' > c || c > '9'))
        break;
    }
    else
      break;
  }

  if (negflg)
    lcval = -lcval;

  if (c != EOF)
  {
    scan_ungetc(c, iop);
    *eofptr = 0;
  }
  else
    *eofptr = 1;

  nchars--;
  if (np == numbuf || (negflg && np == numbuf + 1))  /* gene dykes*/
    return 0;

  if (ptr == NULL)
    return 1;

  *np++ = 0;
  switch((scale << 4) | size)
  {
  case (FLOAT << 4) | SHORT:
  case (FLOAT << 4) | REGULAR:
    *(float *)ptr = atof(numbuf);
    break;

  case (FLOAT << 4) | LONG:
    *(double *)ptr = atof(numbuf);
    break;

  case (FLOAT << 4) | LONGDOUBLE:
    *(long double *)ptr = _atold(numbuf);
    break;

  case (INT << 4) | CHAR:
    *(char *)ptr = (char)lcval;
    break;

  case (INT << 4) | SHORT:
    *(short *)ptr = (short)lcval;
    break;

  case (INT << 4) | REGULAR:
    *(int *)ptr = (int)lcval;
    break;

  case (INT << 4) | LONG:
    *(long *)ptr = (long)lcval;
    break;

  case (INT << 4) | LONGDOUBLE:
    *(long long *)ptr = lcval;
    break;
  }

  return 1;
}

static int
_instr(char *ptr, int type, int len, FILE *iop,
       int (*scan_getc)(FILE *), int (*scan_ungetc)(int, FILE *),
       int *eofptr, const bool allocate_char_buffer,
       const char_set *cset)
{
  register int ch;
  char *arg_ptr = NULL, *orig_ptr = NULL;
  size_t string_length;
  const char_set *ignstp;
  int matched = 0;
  size_t buffer_size = BUFFER_INCREMENT;

  *eofptr = 0;
  if (type == 'c' && len == DEFAULT_WIDTH)
    len = 1;

  if (allocate_char_buffer)
  {
    if (!len)
    {
      errno = ENOMEM;
      return 0;
    }
    else
    {
      arg_ptr = ptr;
      orig_ptr = ptr = malloc(buffer_size);
      if (!ptr)
      {
        errno = ENOMEM;
        return 0;
      }
    }
  }

  ignstp = &no_chars;
  if (type == 's')
    ignstp = &spaces;

  while ((string_length = nchars++, ch = scan_getc(iop)) != EOF && in_charset(ignstp, ch & 0xff))
    ;

  ignstp = &nonspaces;
  if (type == 'c')
    ignstp = &all_chars;
  else if (type == '[')
    ignstp = cset;

  while (ch != EOF && in_charset(ignstp, ch & 0xff))
  {
    matched = 1;
    if (ptr)
      *ptr++ = ch;

    if (allocate_char_buffer && type != 'c')
    {
      if (--buffer_size < 1)
      {
        const ptrdiff_t offset = ptr - orig_ptr;
        char *new_ptr = realloc(orig_ptr, (size_t)(offset + BUFFER_INCREMENT));
        if (!new_ptr)
        {
          free(orig_ptr);
          errno = ENOMEM;
          return 0;
        }
        orig_ptr = new_ptr;
        ptr = orig_ptr + offset;
        buffer_size = BUFFER_INCREMENT;

        if (--len < 1)
          len = DEFAULT_WIDTH;
      }
    }
    else if (--len < 1)
      break;

    ch = scan_getc(iop);
    nchars++;
  }

  if (ch != EOF)
  {
    if (len > 0)
    {
      scan_ungetc(ch, iop);
      nchars--;
    }
    *eofptr = 0;
  }
  else
  {
    nchars--;
    *eofptr = 1;
  }

  if (matched)
  {
    string_length = nchars - string_length;
    if (ptr && type != 'c')
    {
      *ptr++ = '\0';
      string_length++;
    }
    if (allocate_char_buffer)
    {
      char *new_ptr = realloc(orig_ptr, string_length);
      *(char **)arg_ptr = new_ptr;
      ptr = arg_ptr;
      if (!new_ptr)
      {
        free(orig_ptr);
        errno = ENOMEM;
        return 0;
      }
    }

    return 1;
  }

  return 0;
}

static int
_inwstr(wchar_t *ptr, int type, int len, FILE *iop,
        int (*scan_getc)(FILE *), int (*scan_ungetc)(int, FILE *),
        int *eofptr, const bool allocate_char_buffer,
        const char_set *cset)
{
  register int ch;
  wchar_t *arg_ptr = NULL, *orig_ptr = NULL;
  size_t string_length;
  const char_set *ignstp;
  int matched = 0;
  size_t buffer_size = BUFFER_INCREMENT;
  mbstate_t mbs;
  char chrbuf[MB_LEN_MAX];
  unsigned mbcsize = 0;

  wcrtomb(NULL, L'\0', &mbs); /* initial shift state */

  *eofptr = 0;
  if (type == 'c' && len == DEFAULT_WIDTH)
    len = 1;

  if (allocate_char_buffer)
  {
    if (!len)
    {
      errno = ENOMEM;
      return 0;
    }
    else
    {
      arg_ptr = ptr;
      orig_ptr = ptr = malloc(buffer_size * sizeof(wchar_t));
      if (!ptr)
      {
        errno = ENOMEM;
        return 0;
      }
    }
  }

  ignstp = &no_chars;
  if (type == 's')
    ignstp = &spaces;

  while ((string_length = nchars++, ch = scan_getc(iop)) != EOF && in_charset(ignstp, ch & 0xff))
    ;

  ignstp = &nonspaces;
  if (type == 'c')
    ignstp = &all_chars;
  else if (type == '[')
    ignstp = cset;

  while (ch != EOF)
  {
    wchar_t wc;

    matched = 1;

    mbcsize = 0;
    while (1)
    {
      size_t l;
      chrbuf[mbcsize++] = ch;
      l = mbrtowc(&wc, chrbuf, mbcsize, &mbs);
      if (l == (size_t)(-1))
      {
        /* conversion error */
        free(orig_ptr);
        return 0;
      }
      if (l == (size_t)(-2))
      {
        /* character is incomplete */
        ch = scan_getc(iop);
        if (ch == EOF)
        {
          /* conversion error */
          free(orig_ptr);
          errno = EILSEQ;
          return 0;
        }
      }
      else
      {
        break;
      }
    }

    if (!in_charset(ignstp, wc))
      break;

    if (ptr)
      *ptr++ = wc;

    if (allocate_char_buffer && type != 'c')
    {
      if (--buffer_size < 1)
      {
        const ptrdiff_t offset = ptr - orig_ptr;
        wchar_t *new_ptr = realloc(orig_ptr, (size_t)(offset + BUFFER_INCREMENT) * sizeof(wchar_t));
        if (!new_ptr)
        {
          free(orig_ptr);
          errno = ENOMEM;
          return 0;
        }
        orig_ptr = new_ptr;
        ptr = orig_ptr + offset;
        buffer_size = BUFFER_INCREMENT;

        if (--len < 1)
          len = DEFAULT_WIDTH;
      }
    }
    else if (--len < 1)
      break;

    ch = scan_getc(iop);
    nchars++;
  }

  if (ch != EOF)
  {
    while (mbcsize != 0)
    {
      scan_ungetc(chrbuf[--mbcsize], iop);
      nchars--;
    }
    *eofptr = 0;
  }
  else
  {
    nchars--;
    *eofptr = 1;
  }

  if (matched)
  {
    string_length = nchars - string_length;
    if (ptr && type != 'c')
    {
      *ptr++ = L'\0';
      string_length++;
    }
    if (allocate_char_buffer)
    {
      wchar_t *new_ptr = realloc(orig_ptr, string_length * sizeof(wchar_t));
      *(wchar_t **)arg_ptr = new_ptr;
      ptr = arg_ptr;
      if (!new_ptr)
      {
        free(orig_ptr);
        errno = ENOMEM;
        return 0;
      }
    }

    return 1;
  }

  return 0;
}

static char_set *
_getccl(const char **pfmt, int len)
{
  char_set *set;
  size_t set_size;
  unsigned char c;
  const char *s = *pfmt;

  /* Upper bound on number of character ranges */
  set_size = strcspn(s, "]");
  set = malloc(offsetof(char_set, range) + sizeof(set->range[0])*set_size);
  if (set == NULL)
    return NULL;

  set->invert = false;
  if (*s == '^')
  {
    set->invert = true;
    s++;
  }
  set->num_ranges = 0;

  if ((c = (unsigned char)*s) == ']' || c == '-')
  { /* first char is special */
    set->range[0].first = c;
    set->range[0].last  = c;
    set->num_ranges = 1;
    s++;
  }

  if (len == LONG)
  {
    /* %l[...] */
    wchar_t wc1, wc2;
    mbstate_t mbs;
    wcrtomb(NULL, L'\0', &mbs); /* initial shift state */
    while (true)
    {
      size_t l = mbsrtowcs(&wc1, &s, 1, &mbs);
      if (l == (size_t)(-1))
      {
        /* encoding error */
        free(set);
        return NULL;
      }
      if (wc1 == L']' || wc1 == L'\0')
        break;
      set->range[set->num_ranges].first = wc1;
      set->range[set->num_ranges].last  = wc1;
      if (s[0] == '-' && s[1] != ']')
      {
        s++;
        l = mbsrtowcs(&wc2, &s, 1, &mbs);
        if (l == (size_t)(-1))
        {
          /* encoding error */
          free(set);
          return NULL;
        }
        if (wc2 > wc1)
          set->range[set->num_ranges].last  = wc1;
      }
      set->num_ranges++;
    }
  }
  else
  {
    while ((c = (unsigned char)*s++) != ']')
    {
      if (c == 0)
      {
        /* end of string */
        *pfmt = s;
        return set;
      }
      else if (s[0] == '-' && s[1] != ']' && c <= (unsigned char)s[1])
      {
        /* range of characters */
        set->range[set->num_ranges].first = c;
        set->range[set->num_ranges].last  = (unsigned char)s[1];
        set->num_ranges++;
        s += 2;
      }
      else
      {
        /* single character */
        set->range[set->num_ranges].first = c;
        set->range[set->num_ranges].last  = c;
        set->num_ranges++;
      }
    }
  }

  *pfmt = s;
  return set;
}

static bool
in_charset(const char_set *cset, wchar_t chr)
{
  size_t i;

  for (i = 0; i < cset->num_ranges; ++i) {
    if (cset->range[i].first <= chr && chr <= cset->range[i].last)
      break;
  }

  return (i < cset->num_ranges) ^ !!cset->invert;
}
