/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */

#include <fenv.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>
#include <libc/ieee.h>

#if defined (__GNUC__) && (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 8))
# define __gnuc_extension__  __extension__
#else
# define __gnuc_extension__
#endif

#define LONG_DOUBLE_BIAS                                     (0x3FFFU)
#define BIN_DIGITS_IN_FRACTION                               (63)  /*  Amount of binary digits in fraction part of mantissa.  */
#define BIN_DIGITS_IN_MANTISSAH                              (31)  /*  Amount of binary digits in msw of the fraction part of mantissa.  */
#define BIN_DIGITS_IN_MANTISSAL                              (BIN_DIGITS_IN_FRACTION - BIN_DIGITS_IN_MANTISSAH)
#define ALL_DIGITS_ARE_SIGNIFICANT(exp)                      ((exp) > (BIN_DIGITS_IN_FRACTION - 1))
#define NO_SIGNIFICANT_DIGITS_IN_MANTISSAL(exp)              ((exp) < BIN_DIGITS_IN_MANTISSAH)
#define MAGNITUDE_IS_TOO_LARGE(exp)                          ((exp) > (int)(sizeof(long long int) * 8) - 2)
#define MAGNITUDE_IS_LESS_THAN_ONE(exp)                      ((exp) < 0)
#define MAGNITUDE_IS_LESS_THAN_ONE_HALF(exp)                 ((exp) < -1)

#define CARRY_INTO_INTEGER_PART(x)                           ((x) & 0x100000000ULL)
#define ROUND_MANTISSAH_TO_INTEGER(num, unbiased_exponent)                                                 \
(__gnuc_extension__                                                                                        \
  ({                                                                                                       \
     uint64_t rounded_mantissah = (uint64_t)(num).ldt.mantissah + (0x40000000ULL >> (unbiased_exponent));  \
     if (CARRY_INTO_INTEGER_PART(rounded_mantissah))                                                       \
     {                                                                                                     \
       rounded_mantissah >>= 1;                                                                            \
       unbiased_exponent++;                                                                                \
     }                                                                                                     \
     (long long int)(rounded_mantissah >> (BIN_DIGITS_IN_MANTISSAH - (unbiased_exponent)));                \
  })                                                                                                       \
)

#define SHIFT_LEFT_MANTISSAH(num, unbiased_exponent)         ((uint64_t)(num).ldt.mantissah << BIN_DIGITS_IN_MANTISSAL)
#define CONVERT_MANTISSA_TO_INTEGER(num, unbiased_exponent)  ((long long int)((SHIFT_LEFT_MANTISSAH(num, unbiased_exponent) | (uint64_t)(num).ldt.mantissal) << ((unbiased_exponent) - BIN_DIGITS_IN_FRACTION)))
#define ROUND_MANTISSA_TO_INTEGER(num, unbiased_exponent)                                                                                         \
(__gnuc_extension__                                                                                                                               \
  ({                                                                                                                                              \
     uint32_t rounded_mantissal = (uint32_t)(num).ldt.mantissal + (0x80000000UL >> ((unbiased_exponent) - BIN_DIGITS_IN_MANTISSAH));              \
     if (result = (long long int)(num).ldt.mantissah, rounded_mantissal < (num).ldt.mantissal)                                                    \
       result++;                                                                                                                                  \
     if ((unbiased_exponent) > BIN_DIGITS_IN_MANTISSAH)                                                                                           \
       result = result << ((unbiased_exponent) - BIN_DIGITS_IN_MANTISSAH) | rounded_mantissal >> (BIN_DIGITS_IN_FRACTION - (unbiased_exponent));  \
     (long long int)result;                                                                                                                       \
  })                                                                                                                                              \
)


#ifdef __STDC__
long long int
llroundl(long double x)
#else
long long int
llroundl(x)
long double x;
#endif
{
  _longdouble_union_t ieee_value;
  int unbiased_exponent;


  ieee_value.ld = x;
  unbiased_exponent = ieee_value.ldt.exponent - LONG_DOUBLE_BIAS;

  if (MAGNITUDE_IS_TOO_LARGE(unbiased_exponent))  /* The number is too large.  */
    return (long long int)x;                      /* It is left implementation defined what happens.  */
  else
  {
    long long int result;
    int sign = ieee_value.ldt.sign;


    if (NO_SIGNIFICANT_DIGITS_IN_MANTISSAL(unbiased_exponent))
    {
      if (MAGNITUDE_IS_LESS_THAN_ONE(unbiased_exponent))
        result = MAGNITUDE_IS_LESS_THAN_ONE_HALF(unbiased_exponent) ? 0 : 1;
      else
        result = ROUND_MANTISSAH_TO_INTEGER(ieee_value, unbiased_exponent);
    }
    else
    {
      if (ALL_DIGITS_ARE_SIGNIFICANT(unbiased_exponent))
        result = CONVERT_MANTISSA_TO_INTEGER(ieee_value, unbiased_exponent);  /* >= 2^63 is already an exact integer.  */
      else
        result = ROUND_MANTISSA_TO_INTEGER(ieee_value, unbiased_exponent);
    }

    if (ieee_value.ld < (long double)LLONG_MIN
    ||  (long double)LLONG_MAX < ieee_value.ld)
      feraiseexcept(FE_INVALID);
    return sign ? -result : result;
  }
}
