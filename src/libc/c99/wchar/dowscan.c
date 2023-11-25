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
#include <wctype.h>
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
                  wint_t (*scan_getc)(FILE *), wint_t (*scan_ungetc)(wint_t, FILE *),
                  int *eofptr, const bool allocate_char_buffer,
                  const char_set *cset);
static int _instr(char *ptr, int type, int len, FILE *iop,
                  wint_t (*scan_getc)(FILE *), wint_t (*scan_ungetc)(wint_t, FILE *),
                  int *eofptr, const bool allocate_char_buffer,
                  const char_set *cset);
static int _inwstr(wchar_t *ptr, int type, int len, FILE *iop,
                   wint_t (*scan_getc)(FILE *), wint_t (*scan_ungetc)(wint_t, FILE *),
                   int *eofptr, const bool allocate_char_buffer,
                   const char_set *cset);
static char_set *_getccl(const wchar_t **pfmt, int len);
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

static unsigned char _sctab[256] = {
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
static wchar_t decimal_point = L'.';

int
_dowscan(FILE *iop, const wchar_t *fmt, va_list argp)
{
  return(_dowscan_low(iop, fgetwc, ungetwc, fmt, argp));
}

int
_dowscan_low(FILE *iop, wint_t (*scan_getc)(FILE *), wint_t (*scan_ungetc)(wint_t, FILE *), const wchar_t *fmt, va_list argp)
{
  register int ch;
  int nmatch, n, len;
  wint_t ch1;
  int *ptr, fileended, size;
  int suppressed;
  bool allocate_char_buffer;
  int previous_errno = errno;
  const va_list arg_list = argp;
  bool retrieve_arg_ptr;
  char_set *cset;
  bool ok;

  iop->_flag |= _IOBYTE;

  decimal_point = btowc(localeconv()->decimal_point[0]);
  nchars = 0;
  nmatch = 0;
  fileended = 0;
  suppressed = 0;
  errno = 0;

  for (;;)
  {
    switch (ch = *fmt++)
    {
    case L'\0':
      return nmatch;
    case L'%':
      if ((ch = *fmt++) == L'%')
        goto def;

      retrieve_arg_ptr = true;
      allocate_char_buffer = false;
      ptr = NULL;
      cset = NULL;
repeat:
      if (ch != L'*' && retrieve_arg_ptr)
        ptr = va_arg(argp, int *);
      else
        ch = *fmt++;
      n = len = 0;
      size = REGULAR;
      while (iswdigit(ch))
      {
        n = n * 10 + ch - L'0';
        ch = *fmt++;
      }
      if (ch == L'$')
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

      if (ch == L'l')
      {
        size = LONG;
        ch = *fmt++;
        if (ch == L'l')
        {
          size = LONGDOUBLE; /* for long long and long double 'll' format */
          ch = *fmt++;
        }
      }
      else if (ch == L'h')
      {
        size = SHORT;
        ch = *fmt++;
        if (ch == L'h')
        {
          /* C99 */
          /* for 'hh' - char */
          size = CHAR;
          ch = *fmt++;
        }
      }
      else if (ch == L'L')
      {
        size = LONGDOUBLE;
        ch = *fmt++;
      }
      else if (ch == L'j')
      {
        /* C99 */
        size = LONGDOUBLE; /* for long long */
        ch = *fmt++;
      }
      else if (ch == L'z')
      {
        /* C99 */
        size = LONG;
        ch = *fmt++;
      }
      else if (ch == L't')
      {
        /* C99 */
        size = REGULAR;
        ch = *fmt++;
      }
      else if (ch == L'm')
      {
        /* POSIX.1 and GNU glibc extension */
        allocate_char_buffer = true;
        ch = *fmt++;
        if (ch == L'l')
        {
          size = LONG;
          ch = *fmt++;
        }
      }
      if (ch == L'[')
      {
        cset = _getccl(&fmt, size);
        if (cset == NULL)
          return WEOF;
      }

      if (iswupper(ch))
      {
        /* ch = tolower(ch);
           gcc gives warning: ANSI C forbids braced
           groups within expressions */
        ch += L'a' - L'A';
        /* The following if clause is an extension of ANSI/Posix spec: it
           allows to use %D, %U, %I etc. to store value in a long (rather
           than an int) and %lD, %lU etc. to store value in a long long.
           This extension is supported by some compilers (e.g. Borland C).
           Old pre-ANSI compilers, such as Turbo C 2.0, also interpreted
           %E, %F and %G to store in a double (rather than a float), but
           this contradicts the ANSI Standard, so we don't support it.
           %X should be treated as per the ANSI Standard - no length
           is implied by the upper-case x. */
        if (ch == L'd' || ch == L'i' || ch == L'o' || ch == L'u')
        {
          if (size == LONG)
            size = LONGDOUBLE;
          else if (size != LONGDOUBLE)
            size = LONG;
        }
      }
      if (ch == L'\0')
        return WEOF;

      if (ch == L'n')
      {
        if (!ptr)
          break;
        if (size == LONG)
          *(long *)ptr = nchars;
        else if (size == CHAR)
          *(signed char *)ptr = nchars;
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
          return WEOF;

        errno = previous_errno;
        return nmatch;
      }
      break;
    case L' ':
    case L'\n':
    case L'\t':
    case L'\r':
    case L'\f':
    case L'\v':
      while (((nchars++, ch1 = scan_getc(iop)) != WEOF) && ch1 < (int)sizeof(_sctab) && (_sctab[ch1] & SPC))
        ;

      if (ch1 != WEOF)
        scan_ungetc(ch1, iop);

      nchars--;
      break;

    default:
def:
      ch1 = scan_getc(iop);
      if (ch1 != WEOF) nchars++;
      if (ch1 != ch)
      {
        if (ch1 == WEOF)
          return (nmatch || suppressed ? nmatch : WEOF);
        scan_ungetc(ch1, iop);
        nchars--;
        return nmatch;
      }
    }
  }
}

static int
_innum(int *ptr, int type, int len, int size, FILE *iop,
       wint_t (*scan_getc)(FILE *), wint_t (*scan_ungetc)(wint_t, FILE *),
       int *eofptr, const bool allocate_char_buffer,
       const char_set *cset)
{
  register wchar_t *np;
  wchar_t numbuf[64];
  register int c, base;
  int expseen, scale, negflg, c1, ndigit;
  long long lcval;
  int cpos;

  if (type == L'c' || type == L's' || type == L'[')
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
  if (type == L'a' || type == L'e' || type == L'f' || type == L'g')
    scale = FLOAT;
  base = 10;
  if (type == L'o')
    base = 8;
  else if (type == L'x' || type == L'p' || type == L'a')
    base = 16;
  np = numbuf;

  expseen = 0;
  negflg = 0;
  while (((nchars++, c = scan_getc(iop)) != WEOF) && c < (int)sizeof(_sctab) && (_sctab[c] & SPC))
    ;
  if (c == WEOF) nchars--;
  if (c == L'-')
  {
    negflg++;
    *np++ = c;
    c = scan_getc(iop);
    nchars++;
    len--;
  }
  else if (c == L'+')
  {
    len--;
    c = scan_getc(iop);
    nchars++;
  }

  cpos = 0;
  for (; --len >= 0; *np++ = c, c = scan_getc(iop), nchars++)
  {
    cpos++;
    if (c == L'0' && cpos == 1 && type == L'i')
      base = 8;
    if ((c == L'x' || c == L'X') && (type == L'a' || type == L'i' || type == L'x')
        && cpos == 2 && lcval == 0)
    {
      base = 16;
      continue;
    }
    if ((c != WEOF && iswdigit(c)  && c - L'0' < base)
        || (base == 16 && ((L'a' <= c && c <= L'f') || (L'A' <= c && c <= L'F'))))
    {
      ndigit++;
      if (base == 8)
        lcval <<= 3;
      else if (base == 10)
        lcval = ((lcval << 2) + lcval) << 1;
      else
        lcval <<= 4;
      c1 = c;
      if (iswdigit(c))
        c -= L'0';
      else if (L'a' <= c && c <= L'f')
        c -= L'a' - 10;
      else
        c -= L'A' - 10;
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
    else if ((c == L'e' || c == L'E') && expseen == 0)
    {
      if (scale == INT || base == 8 || ndigit == 0)
        break;
      expseen++;
      *np++ = c;
      c = scan_getc(iop);
      nchars++;
      if (c != L'+' && c != L'-' && (L'0' > c || c > L'9'))
        break;
    }
    else
      break;
  }

  if (negflg)
    lcval = -lcval;

  if (c != WEOF)
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
    *(float *)ptr = wcstof(numbuf, NULL);
    break;

  case (FLOAT << 4) | LONG:
    *(double *)ptr = wcstod(numbuf, NULL);
    break;

  case (FLOAT << 4) | LONGDOUBLE:
    *(long double *)ptr = wcstold(numbuf, NULL);
    break;

  case (INT << 4) | CHAR:
    *(signed char *)ptr = (signed char)lcval;
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
       wint_t (*scan_getc)(FILE *), wint_t (*scan_ungetc)(wint_t, FILE *),
       int *eofptr, const bool allocate_char_buffer,
       const char_set *cset)
{
  wint_t ch;
  char *arg_ptr = NULL, *orig_ptr = NULL;
  size_t string_length;
  const char_set *ignstp;
  int matched = 0;
  size_t buffer_size = BUFFER_INCREMENT;
  mbstate_t mbs;

  *eofptr = 0;
  if (type == L'c' && len == DEFAULT_WIDTH)
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
  if (type == L's')
    ignstp = &spaces;

  while ((string_length = nchars++, ch = scan_getc(iop)) != WEOF && in_charset(ignstp, ch))
    ;

  ignstp = &nonspaces;
  if (type == L'c')
    ignstp = &all_chars;
  else if (type == L'[')
    ignstp = cset;

  wcrtomb(NULL, L'\0', &mbs);
  while (ch != WEOF && in_charset(ignstp, ch))
  {
    char mbch[MB_LEN_MAX];
    size_t l, i;

    matched = 1;

    l = wcrtomb(mbch, ch, &mbs);
    if (l == (size_t)(-1)) {
      break; /* encoding error */
    }

    for (i = 0; i < l; ++i) {
      if (ptr) {
        *ptr++ = mbch[i];
      }

      if (allocate_char_buffer && type != L'c')
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
    }
    if (len < 1) {
      break;
    }

    ch = scan_getc(iop);
    nchars++;
  }

  if (ch != WEOF)
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
    if (ptr && type != L'c')
    {
      *ptr++ = L'\0';
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
        wint_t (*scan_getc)(FILE *), wint_t (*scan_ungetc)(wint_t, FILE *),
        int *eofptr, const bool allocate_char_buffer,
        const char_set *cset)
{
  wint_t ch;
  wchar_t *arg_ptr = NULL, *orig_ptr = NULL;
  size_t string_length;
  const char_set *ignstp;
  int matched = 0;
  size_t buffer_size = BUFFER_INCREMENT;

  *eofptr = 0;
  if (type == L'c' && len == DEFAULT_WIDTH)
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
  if (type == L's')
    ignstp = &spaces;

  while ((string_length = nchars++, ch = scan_getc(iop)) != WEOF && in_charset(ignstp, ch))
    ;

  ignstp = &nonspaces;
  if (type == L'c')
    ignstp = &all_chars;
  else if (type == L'[')
    ignstp = cset;

  while (ch != WEOF)
  {
    wchar_t wc = ch;

    matched = 1;

    if (!in_charset(ignstp, wc))
      break;

    if (ptr)
      *ptr++ = wc;

    if (allocate_char_buffer && type != L'c')
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

  if (ch != WEOF)
  {
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
    if (ptr && type != L'c')
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
_getccl(const wchar_t **pfmt, int len)
{
  char_set *set;
  size_t set_size;
  wchar_t c;
  const wchar_t *s = *pfmt;

  /* Upper bound on number of character ranges */
  set_size = wcscspn(s, L"]");
  set = malloc(offsetof(char_set, range) + sizeof(set->range[0])*set_size);
  if (set == NULL)
    return NULL;

  set->invert = false;
  if (*s == L'^')
  {
    set->invert = true;
    s++;
  }
  set->num_ranges = 0;

  if ((c = *s) == L']' || c == L'-')
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
    while (true)
    {
      wc1 = *s++;
      if (wc1 == L']' || wc1 == L'\0')
        break;
      set->range[set->num_ranges].first = wc1;
      set->range[set->num_ranges].last  = wc1;
      if (s[0] == L'-' && s[1] != L']')
      {
        s++;
        wc2 = *s++;
        if (wc2 > wc1)
          set->range[set->num_ranges].last  = wc1;
      }
      set->num_ranges++;
    }
  }
  else
  {
    while ((c = *s++) != L']')
    {
      if (c == 0)
      {
        /* end of string */
        *pfmt = s;
        return set;
      }
      else if (s[0] == L'-' && s[1] != L']' && c <= s[1])
      {
        /* range of characters */
        set->range[set->num_ranges].first = c;
        set->range[set->num_ranges].last  = s[1];
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
