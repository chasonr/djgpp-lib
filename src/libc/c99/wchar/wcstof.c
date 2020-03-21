/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2008 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <libc/stubs.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <errno.h>
#include <wctype.h>
#include <wchar.h>
#include <libc/unconst.h>
#include <libc/ieee.h>


#define MANTISSA_SIZE       (23)     /*  Number binary digits in the fractional part of the mantissa.  */
#define HEX_DIGIT_SIZE      (4)
#define FLOAT_BIAS          (0x7FU)
#define MAX_BIN_EXPONENT    (127)   /*  Max. and min. binary exponent (inclusive) as  */
#define MIN_BIN_EXPONENT    (-126)  /*  defined in Intel manual (253665.pdf, Table 4.2).  */
#define IS_ZERO_DIGIT(x)    ((x) == L'0')
#define IS_DEC_DIGIT(x)     (((x) >= L'0') && ((x) <= L'9'))
#define IS_HEX_DIGIT(x)     ((((x) >= L'A') && ((x) <= L'F')) || \
                             (((x) >= L'a') && ((x) <= L'f')) || \
                             IS_DEC_DIGIT(x))
#define IS_DEC_EXPONENT(x)  (((x[0]) == L'E' || (x[0]) == L'e') && \
                             ((x[1] == L'+' &&  IS_DEC_DIGIT(x[2])) || \
                              (x[1] == L'-' &&  IS_DEC_DIGIT(x[2])) || \
                             IS_DEC_DIGIT(x[1])))
#define IS_HEX_EXPONENT(x)  (((x[0]) == L'P' || (x[0]) == L'p') && \
                             ((x[1] == L'+' &&  IS_DEC_DIGIT(x[2])) || \
                              (x[1] == L'-' &&  IS_DEC_DIGIT(x[2])) || \
                             IS_DEC_DIGIT(x[1])))

static int case_equal(const wchar_t *s1, const wchar_t *s2);

float
wcstof(const wchar_t *s, wchar_t **sret)
{
  long double r = 0;            /* result */
  int e = 0;                    /* exponent */
  long double d;                /* scale */
  int sign = 1;                 /* +- 1.0 */
  int esign = 1;
  int i;
  int flags = 0;
  int overflow = 0;
  char radix_point = localeconv()->decimal_point[0];


  if (sret)
    *sret = unconst(s, wchar_t *);

  while (iswspace(*s))
    s++;

  if (!*s)
    return 0.0;

  /* Handle leading sign. */
  if (*s == L'+')
    s++;
  else if (*s == L'-')
  {
    sign = -1;
    s++;
  }

  /* Handle INF and INFINITY. */
  if (case_equal(L"INF", s))
  {
    if (sret)
    {
      if (case_equal( L"INITY", &s[3]))
        *sret = unconst((&s[8]), wchar_t *);
      else
        *sret = unconst((&s[3]), wchar_t *);
    }

    return (sign < 0) ? -INFINITY : INFINITY;
  }

  /* Handle NAN and NAN(<hex-number>). */
  if (case_equal(L"NAN", s))
  {
    _float_union_t t;

    t.f = NAN;

    if (sign < 0)
      t.ft.sign = 1;

    if (s[3] == L'(')
    {
      unsigned long mantissa_bits = 0;
      wchar_t *endptr = unconst((&s[4]), wchar_t *);

      mantissa_bits = wcstoul(&s[4], &endptr, 0);
      if (*endptr == L')')
      {
        mantissa_bits = mantissa_bits & 0x7fffff;
        if (mantissa_bits)
          t.ft.mantissa = mantissa_bits;
        if (sret)
          *sret = endptr + 1;

        return t.f;
      }

      /* The subject sequence didn't match NAN(<number>),
         so match only NAN. */
    }

    if (sret)
      *sret = unconst((&s[3]), wchar_t *);

    return t.f;
  }

  /* Handle 0xH.HHH[p|P][+|-]DDD. */
  if (case_equal(L"0X", s) && (s[2] == L'.' || IS_HEX_DIGIT(s[2])))
  {
    const int max_digits = 1 + MANTISSA_SIZE / HEX_DIGIT_SIZE + 1;  /* One more digit than fits into mantissa.  */
    int bin_exponent, digits, integer_digits;
    unsigned long int mantissa, msb_mask;
    _float_union_t ieee754;


    /*
     *  Mantissa.
     *  6 hex digits fit into the mantissa
     *  including the implicit integer bit.
     */
    bin_exponent = 0;
    integer_digits = 0;
    msb_mask = mantissa = 0x00UL;
    s += 2;  /*  Skip the hex prefix.  */
    while (integer_digits < max_digits && IS_HEX_DIGIT(*s))
    {
      flags = 1;
      mantissa <<= HEX_DIGIT_SIZE;
      mantissa |= IS_DEC_DIGIT(*s) ? *s - L'0' :
                  ((*s >= L'A') && (*s <= L'F')) ? *s - L'A' + 10 : *s - L'a' + 10;
      if (mantissa)        /*  Discarts leading zeros.  */
        integer_digits++;  /*  Counts hex digits.  16**integer_digits.  */
      s++;
    }
    if (integer_digits)
    {
      /*
       *  Compute the binary exponent for a normalized mantissa by
       *  shifting the radix point inside the most significant hex digit.
       */

      for (digits = 0; IS_HEX_DIGIT(*s); s++)
        digits++;  /*  Counts hex digits.  */

      msb_mask = 0x01UL;
      bin_exponent = integer_digits * HEX_DIGIT_SIZE - 1;  /*  2**bin_exponent.  */
      for (msb_mask <<= bin_exponent; !(mantissa & msb_mask); msb_mask >>= 1)
        bin_exponent--;
      bin_exponent += digits * HEX_DIGIT_SIZE;
      integer_digits += digits;
    }

    digits = integer_digits;
    if (*s == radix_point)
    {
      int extra_shifts, fraction_zeros = 0;

      s++;
      while ((digits - fraction_zeros) < max_digits && IS_HEX_DIGIT(*s))
      {
        flags = 1;
        digits++;  /*  Counts hex digits.  */
        mantissa <<= HEX_DIGIT_SIZE;
        mantissa |= IS_DEC_DIGIT(*s) ? *s - L'0' :
                    ((*s >= L'A') && (*s <= L'F')) ? *s - L'A' + 10 : *s - L'a' + 10;
        if (mantissa == 0)
          fraction_zeros++;  /*  Counts hex zeros.  16**(-fraction_zeros + 1).  */
        s++;
      }
      if (!integer_digits && mantissa)
      {
        /*
         *  Compute the binary exponent for a normalized mantissa by
         *  shifting the radix point inside the most significant hex digit.
         */

        msb_mask = 0x01UL;
        bin_exponent = -fraction_zeros * HEX_DIGIT_SIZE;  /*  2**bin_exponent.  */
        for (msb_mask <<= (digits * HEX_DIGIT_SIZE + bin_exponent); !(mantissa & msb_mask); msb_mask >>= 1)
          bin_exponent--;
      }
      else if ((extra_shifts = digits - integer_digits) > 0)
        msb_mask <<= extra_shifts * HEX_DIGIT_SIZE;
    }

    if (digits >= max_digits)
    {
      /*
       *  Round half towards plus infinity (round half up).
       */
      const int lsd = 0x0000000FUL & mantissa;  /*  Least significant hex digit.  Will be rounded out.  */
      if (lsd > 0x07)
      {
        mantissa += 0x00000010UL;  /* Smallest float greater than x.  */
        if (!(mantissa & msb_mask))
        {
          /*  Overflow.  */
          mantissa >>= 1;
          bin_exponent++;
        }
      }
    }

    if (flags == 0)
    {
      errno = EINVAL;  /*  No valid mantissa, no conversion could be performed.  */
      return 0.0;
    }

    if (sret)
      *sret = unconst(s, wchar_t *);

    if (mantissa)
    {
      /*
       *  Normalize mantissa.
       */
      while (!(mantissa & 0x80000000UL))
        mantissa <<= 1;  /*  Shift a binary 1 into the integer part of the mantissa.  */
      mantissa >>= (31 - 23);
      /*  At this point the mantissa is normalized and the exponent has been adjusted accordingly.  */
    }


    /*
     *  After discarting all hex digits left,
     *  if the next character is P or p
     *  continue with the extracting of the
     *  exponent, else any other character
     *  that have appeared terminates the number.
     */
    while (IS_HEX_DIGIT(*s))
      s++;

    /*
     *  Exponent.
     */
    if (IS_HEX_EXPONENT(s))
    {
      int exponent = 0.0;

      s++;
      if (*s == L'+')
        s++;
      else if (*s == L'-')
      {
        esign = -1;
        s++;
      }

      while ((esign * exponent + bin_exponent) < (MAX_BIN_EXPONENT + 1) && IS_DEC_DIGIT(*s))
      {
        exponent *= 10;
        exponent += *s - L'0';
        s++;
      }
      bin_exponent += esign * exponent;  /*  2**bin_exponent.  */
      while (IS_DEC_DIGIT(*s))
        s++;  /*  Discart rest of exponent.  */
    }


    if (sret)
      *sret = unconst(s, wchar_t *);

    if (mantissa)
    {
      if (bin_exponent > MAX_BIN_EXPONENT)
      {
        errno = ERANGE;
        return sign * HUGE_VALF;
      }
      else if(bin_exponent < MIN_BIN_EXPONENT)
      {
        errno = ERANGE;
        return 0.0;
      }
      ieee754.ft.sign     = (sign == 1) ? 0 : 1;
      ieee754.ft.exponent = 0x07FFUL & (bin_exponent + FLOAT_BIAS);
      ieee754.ft.mantissa = 0x007FFFFFUL & mantissa;
    }
    else
      ieee754.f = sign * 0.0;

    return ieee754.f;
  }

  /* Handle ordinary numbers. */
  while (IS_DEC_DIGIT(*s))
  {
    flags |= 1;
    r *= 10.0;
    r += *s - L'0';
    s++;
  }

  if (*s == radix_point)
  {
    d = 0.1L;
    s++;
    while (IS_DEC_DIGIT(*s))
    {
      flags |= 2;
      r += d * (*s - L'0');
      s++;
      d *= 0.1L;
    }
  }
  if (flags == 0)
  {
    errno = EINVAL;  /*  No valid mantissa, no conversion could be performed.  */
    return 0.0;
  }

  if (sret)
    *sret = unconst(s, wchar_t *);

  if (IS_DEC_EXPONENT(s))
  {
    s++;
    if (*s == L'+')
      s++;
    else if (*s == L'-')
    {
      s++;
      esign = -1;
    }
    while (IS_DEC_DIGIT(*s))
    {
      e *= 10;
      e += *s - L'0';
      s++;
    }
  }

  /* Detect overflow.  */
  if (e < 0)
  {
    errno = ERANGE;
    r = 0.0;
    overflow = 1;
  }
  else if (esign < 0)
  {
    const int exponent = e + 1;
    for (i = 1; i < exponent; i++)
    {
      r *= 0.1L;
      /* Detect underflow below 2^-150, which is half
         the smallest representable float. */
      if (r < 7.00649232162408535461e-46L)
      {
        errno = ERANGE;
        r = 0.0;
        break;
      }
    }
  }
  else
  {
    const int exponent = e + 1;
    for (i = 1; i < exponent; i++)
    {
      r *= 10.0;
      if (r > FLT_MAX)  /* detect overflow */
      {
        errno = ERANGE;
        r = 0;
        overflow = 1;
        break;
      }
    }
  }

  if (sret)
    *sret = unconst(s, wchar_t *);

  return !overflow ? r * sign : HUGE_VALF * sign;
}

static int
case_equal(const wchar_t *s1, const wchar_t *s2)
{
  for (size_t i = 0; s1[i] != L'\0'; ++i)
  {
    if (s1[i] != towupper(s2[i]))
      return 0;
  }
  return 1;
}
