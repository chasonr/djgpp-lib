/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
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


#define MANTISSA_SIZE       (52)     /*  Number binary digits in the fractional part of the mantissa.  */
#define HEX_DIGIT_SIZE      (4)
#define DOUBLE_BIAS         (0x3FFU)
#define MAX_BIN_EXPONENT    (1023)   /*  Max. and min. binary exponent (inclusive) as  */
#define MIN_BIN_EXPONENT    (-1022)  /*  defined in Intel manual (253665.pdf, Table 4.2).  */
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

double
wcstod(const wchar_t *s, wchar_t **sret)
{
  long double r = 0;            /* result */
  int e = 0;                    /* exponent */
  long double d;                /* scale */
  int sign = 1;                 /* +- 1.0 */
  int esign = 1;
  int i;
  int flags = 0;
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
      if (case_equal(L"INITY", &s[3]))
        *sret = unconst((&s[8]), wchar_t *);
      else
        *sret = unconst((&s[3]), wchar_t *);
    }

    return (sign < 0) ? -INFINITY : INFINITY;
  }

  /* Handle NAN and NAN(<whatever>). */
  if (case_equal(L"NAN", s))
  {
    _double_union_t t;

    t.d = NAN;

    if (sign < 0)
      t.dt.sign = 1;

    if (s[3] == L'(')
    {
      unsigned long long mantissa_bits = 0;
      wchar_t *endptr = unconst((&s[4]), wchar_t *);

      mantissa_bits = wcstoull(&s[4], &endptr, 16);
      if (*endptr == L')')
      {
        mantissa_bits = mantissa_bits & 0xfffffffffffffULL;
        if (mantissa_bits)
        {
          t.dt.mantissal = mantissa_bits & 0xffffffff;
          t.dt.mantissah = (mantissa_bits >> 32) & 0xfffff;
        }
        if (sret)
          *sret = endptr + 1;

        return t.d;
      }

      /* The subject sequence didn't match NAN(<hex-number>),
         so match only NAN. */
    }

    if (sret)
      *sret = unconst((&s[3]), wchar_t *);

    return t.d;
  }

  /* Handle 0xH.HHH[p|P][+|-]DDD. */
  if (case_equal(L"0X", s) && (s[2] == L'.' || IS_HEX_DIGIT(s[2])))
  {
    const int max_digits = 1 + MANTISSA_SIZE / HEX_DIGIT_SIZE + 1;  /* Two more digits than fit into mantissa.  */
    int bin_exponent, digits, integer_digits;
    unsigned long long int mantissa, msb_mask;
    _double_union_t ieee754;


    /*
     *  Mantissa.
     *  13 hex digits fit into the fraction part.
     */
    bin_exponent = 0;
    integer_digits = 0;
    msb_mask = mantissa = 0x00ULL;
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

      msb_mask = 0x01ULL;
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
      digits = integer_digits;
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

        msb_mask = 0x01ULL;
        bin_exponent = -fraction_zeros * HEX_DIGIT_SIZE;  /*  2**bin_exponent.  */
        for (msb_mask <<= (digits * HEX_DIGIT_SIZE + bin_exponent); !(mantissa & msb_mask); msb_mask >>= 1)
          bin_exponent--;
      }
      else if ((extra_shifts = digits - integer_digits) > 0)
        msb_mask <<= extra_shifts * HEX_DIGIT_SIZE;
    }

    if (flags == 0)
    {
      errno = EINVAL;  /*  No valid mantissa, no conversion could be performed.  */
      return 0.0L;
    }

    if (sret)
      *sret = unconst(s, wchar_t *);

    if (digits >= max_digits)
    {
      /*
       *  Round half towards plus infinity (round half up).
       */
      const int lsd = 0x000000000000000FULL & mantissa;  /*  Least significant hex digit.  Will be rounded out.  */
      if (lsd > 0x07)
      {
        mantissa += 0x0000000000000010ULL;  /* Smallest float greater than x.  */
        if (!(mantissa & msb_mask))
        {
          /*  Overflow.  */
          mantissa >>= 1;
          bin_exponent++;
        }
      }
    }

    if (mantissa)
    {
      /*
       *  Normalize mantissa.
       */
      while (!(mantissa & 0x8000000000000000ULL))
        mantissa <<= 1;  /*  Shift a binary 1 into the integer part of the mantissa.  */
      mantissa >>= (63 - 52);
      /*  At this point the mantissa is normalized and the exponent has been adjusted accordingly.  */
    }


    /*
     *  After discarting all hex digits left,
     *  if the next character is P or p
     *  continue with the extraction of the
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
      long int exponent = 0.0;

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
        return sign * HUGE_VAL;
      }
      else if(bin_exponent < MIN_BIN_EXPONENT)
      {
        errno = ERANGE;
        return 0.0;
      }
      ieee754.dt.sign      = (sign == 1) ? 0 : 1;
      ieee754.dt.exponent  = 0x7FFFU & (bin_exponent + DOUBLE_BIAS);
      ieee754.dt.mantissah = 0x000FFFFFUL & (mantissa >> 32);
      ieee754.dt.mantissal = 0xFFFFFFFFUL & mantissa;
    }
    else
      ieee754.d = sign * 0.0;

    return ieee754.d;
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
    r = HUGE_VAL;
  }
  else if (esign < 0)
  {
    const int exponent = e + 1;
    for (i = 1; i < exponent; i++)
    {
      r *= 0.1L;
      /* Detect underflow below 2^-1075, which is half
         the smallest representable double. */
      if (r < 2.47032822920623272088e-324L)
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
      if (r > DBL_MAX)  /* detect overflow */
      {
        errno = ERANGE;
        r = HUGE_VAL;
        break;
      }
    }
  }

  if (sret)
    *sret = unconst(s, wchar_t *);

  return r * sign;
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
