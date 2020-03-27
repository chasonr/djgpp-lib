/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2010 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2008 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <wchar.h>
#include <time.h>
#include <wctype.h>


#define THURSDAY       4
#define SATURDAY       6
#define SUNDAY         7

#define TM_YEAR_BASE   1900
#define IS_LEAP(year)  ((((year) % 4) == 0) && ((((year) % 100) != 0) || (((year) % 400) == 0)))

static const wchar_t *afmt[] = {
  L"Sun", L"Mon", L"Tue", L"Wed", L"Thu", L"Fri", L"Sat",
};
static const wchar_t *Afmt[] = {
  L"Sunday", L"Monday", L"Tuesday", L"Wednesday", L"Thursday", L"Friday",
  L"Saturday",
};
static const wchar_t *bfmt[] = {
  L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun", L"Jul", L"Aug", L"Sep",
  L"Oct", L"Nov", L"Dec",
};
static const wchar_t *Bfmt[] = {
  L"January", L"February", L"March", L"April", L"May", L"June", L"July",
  L"August", L"September", L"October", L"November", L"December",
};
static const wchar_t __ISO8601_date_format[] = L"%Y-%m-%d";
wchar_t __dj_date_format[10] = L"%m/%d/%y";
wchar_t __dj_time_format[16] = L"%H:%M:%S";

static size_t gsize;
static wchar_t *pt;

static __inline__ int
_compute_iso_wday_of_jan_01(const struct tm *t)
{
  /*
   *  ISO week starts with Monday = 1 and ends with Sunday = 7.
   */

  int wday_jan_01;


  wday_jan_01 = (7 + t->tm_wday - t->tm_yday % 7) % 7;
  if (wday_jan_01 == 0)
    wday_jan_01 = 7;

  return wday_jan_01;
}

static int
_compute_iso_standard_week(const struct tm *t)
{
  /*
   *  In ISO 8601:2000 standard week-based year system,
   *  weeks begin on a Monday and week 1 of the year is
   *  the week that includes January 4th, which is also
   *  the week that includes the first Thursday of the
   *  year, and is also the first week that contains at
   *  least four days in the year.
   */

  int iso_wday_of_jan_01, iso_week;


  iso_wday_of_jan_01 = _compute_iso_wday_of_jan_01(t);  /*  Mon = 1, ..., Sun = 7.  */
  iso_week = (6 + t->tm_yday - (6 + t->tm_wday) % 7) / 7;
  if (iso_week == 0 && iso_wday_of_jan_01 > THURSDAY)   /*  Week belongs to the previous year.  */
  {
    if ((iso_wday_of_jan_01 == SUNDAY) ||
        (iso_wday_of_jan_01 == SATURDAY && !IS_LEAP(t->tm_year - 1 + TM_YEAR_BASE)))
      iso_week = 52;
    else
      iso_week = 53;
  }
  else
  {
    int is_leap_year = IS_LEAP(t->tm_year + TM_YEAR_BASE);
    int iso_wday_of_dec_31 = (365 + is_leap_year - t->tm_yday + (6 + t->tm_wday) % 7) % 7;  /*  Mon = 1, ..., Sun = 7.  */

    if (t->tm_yday > (360 + is_leap_year) && iso_wday_of_dec_31 < THURSDAY)  /*  Belongs to the following year.  */
      iso_week = 1;
    else  /*  Belongs to the current year.  */
      iso_week++;
  }

  return iso_week;
}

static int
_compute_iso_week_based_year(const struct tm *t)
{
  /*
   *  ISO 8601:2000 standard week-based year system.
   */

  int iso_wday_of_jan_01, iso_year, week;


  iso_wday_of_jan_01 = _compute_iso_wday_of_jan_01(t);  /*  Mon = 1, ..., Sun = 7.  */
  week = (6 + t->tm_yday - (6 + t->tm_wday) % 7) / 7;
  if (week == 0 && iso_wday_of_jan_01 > THURSDAY)  /*  Belongs to the previous year.  */
    iso_year = t->tm_year - 1 + TM_YEAR_BASE;
  else
  {
    int is_leap_year = IS_LEAP(t->tm_year + TM_YEAR_BASE);
    int iso_wday_of_dec_31 = (365 + is_leap_year - t->tm_yday + (6 + t->tm_wday) % 7) % 7;  /*  Mon = 1, ..., Sun = 7.  */

    if (t->tm_yday > (360 + is_leap_year) && iso_wday_of_dec_31 < THURSDAY)  /*  Belongs to the following year.  */
      iso_year = t->tm_year + 1 + TM_YEAR_BASE;
    else  /*  Belongs to the current year.  */
      iso_year = t->tm_year + TM_YEAR_BASE;
  }

  return iso_year;
}

static int
_add(const wchar_t *str, int upcase)
{
  for (;; ++pt, --gsize)
  {
    if (!gsize)
      return 0;
    if (!(*pt = *str++))
      return 1;
    if (upcase)
      *pt = towupper(*pt);
  }
}

static int
_conv(int n, int digits, wchar_t pad)
{
  static wchar_t buf[10];
  wchar_t *p = buf + sizeof(buf)/sizeof(buf[0]) - 2;

  do {
    *p-- = n % 10 + L'0';
    n /= 10;
    --digits;
  } while (n > 0 && p > buf);

  if (pad)
    while (p > buf && digits-- > 0)
      *p-- = pad;
  return _add(++p, 0);
}

static size_t
_fmt(const wchar_t *format, const struct tm *t, int upcase)
{
  for (; *format; ++format)
  {
    if (*format == L'%')
    {
      int flag_seen, pad = L'0', space=L' ', swap_case = 0;

      /*  Parse flags.  */
      do {
        flag_seen = 0;
        if (format[1] == L'_')
          flag_seen = 1, pad = space = L' ', format++;
        if (format[1] == L'-')
          flag_seen = 1, pad = space = 0, format++;
        if (format[1] == L'0')
          flag_seen = 1, pad = space = L'0', format++;
        if (format[1] == L'^')
          flag_seen = 1, upcase = 1, format++;
        if (format[1] == L'#')
          flag_seen = 1, swap_case = 1, format++;
      } while (flag_seen);

      /*  Parse modifiers.  */
      if (format[1] == L'E' || format[1] == L'O')
        format++;  /*  Only C/POSIX locale is supported.  */

      switch(*++format)
      {
      case L'\0':
        --format;
        break;
      case L'A':
        if (swap_case)
          upcase = 1;
        if (t->tm_wday < 0 || t->tm_wday > 6)
          return 0;
        if (!_add(Afmt[t->tm_wday], upcase))
          return 0;
        continue;
      case L'a':
        if (swap_case)
          upcase = 1;
        if (t->tm_wday < 0 || t->tm_wday > 6)
          return 0;
        if (!_add(afmt[t->tm_wday], upcase))
          return 0;
        continue;
      case L'B':
        if (swap_case)
          upcase = 1;
        if (t->tm_mon < 0 || t->tm_mon > 11)
          return 0;
        if (!_add(Bfmt[t->tm_mon], upcase))
          return 0;
        continue;
      case L'b':
      case L'h':
        if (swap_case)
          upcase = 1;
        if (t->tm_mon < 0 || t->tm_mon > 11)
          return 0;
        if (!_add(bfmt[t->tm_mon], upcase))
          return 0;
        continue;
      case L'C':
        if (!_conv((t->tm_year + TM_YEAR_BASE) / 100, 2, pad))
          return 0;
        continue;
      case L'c':
        if (!_fmt(L"%a %b %e %H:%M:%S %Y", t, upcase))
          return 0;
        continue;
      case L'e':
        if (!_conv(t->tm_mday, 2, L' '))
          return 0;
        continue;
      case L'D':
        if (!_fmt(L"%m/%d/%y", t, upcase))
          return 0;
        continue;
      case L'd':
        if (!_conv(t->tm_mday, 2, pad))
          return 0;
        continue;
      case L'F':
        if (!_fmt(__ISO8601_date_format, t, upcase))
          return 0;
        continue;
      case L'G':
        if (!_conv(_compute_iso_week_based_year(t), 4, pad))
          return 0;
        continue;
      case L'g':
        if (!_conv(_compute_iso_week_based_year(t) % 100, 2, pad))
          return 0;
        continue;
      case L'H':
        if (!_conv(t->tm_hour, 2, pad))
          return 0;
        continue;
      case L'I':
        if (!_conv(t->tm_hour % 12 ?
                   t->tm_hour % 12 : 12, 2, pad))
          return 0;
        continue;
      case L'j':
        if (!_conv(t->tm_yday + 1, 3, pad))
          return 0;
        continue;
      case L'k':
        if (!_conv(t->tm_hour, 2, L' '))
          return 0;
        continue;
      case L'l':
        if (!_conv(t->tm_hour % 12 ?
                   t->tm_hour % 12 : 12, 2, L' '))
          return 0;
        continue;
      case L'M':
        if (!_conv(t->tm_min, 2, pad))
          return 0;
        continue;
      case L'm':
        if (!_conv(t->tm_mon + 1, 2, pad))
          return 0;
        continue;
      case L'n':
        if (!_add(L"\n", upcase))
          return 0;
        continue;
      case L'P':
        if (!_add(t->tm_hour >= 12 ? L"pm" : L"am", upcase))
          return 0;
        continue;
      case L'p':
        upcase = swap_case ? 0 : 1;
        if (!_add(t->tm_hour >= 12 ? L"pm" : L"am", upcase))
          return 0;
        continue;
      case L'R':
        if (!_fmt(L"%H:%M", t, upcase))
          return 0;
        continue;
      case L'r':
        if (!_fmt(L"%I:%M:%S %p", t, upcase))
          return 0;
        continue;
      case L'S':
        if (!_conv(t->tm_sec, 2, pad))
          return 0;
        continue;
      case L's':
        {
          struct tm _t;
          time_t _time;

          _t = *t;
          _time = mktime(&_t);
          if (_time == (time_t)-1 || !_conv(_time, -1, pad))
            return 0;
        }
        continue;
      case L'T':
        if (!_fmt(L"%H:%M:%S", t, upcase))
          return 0;
        continue;
      case L't':
        if (!_add(L"\t", upcase))
          return 0;
        continue;
      case L'u':
        if (!_conv(t->tm_wday==0 ? 7 : t->tm_wday, 1, pad))
          return 0;
        continue;
      case L'U':
        if (!_conv((t->tm_yday + 7 - t->tm_wday) / 7, 2, pad))
          return 0;
        continue;
      case L'V':
        if (!_conv(_compute_iso_standard_week(t), 2, pad))
          return 0;
        continue;
      case L'W':
        if (!_conv((t->tm_yday + 7 -
                    (t->tm_wday ? (t->tm_wday - 1) : 6))
                   / 7, 2, pad))
          return 0;
        continue;
      case L'w':
        if (!_conv(t->tm_wday, 1, pad))
          return 0;
        continue;
      case L'X':
        if (!_fmt(__dj_time_format, t, upcase))
          return 0;
        continue;
      case L'x':
        if (!_fmt(__dj_date_format, t, upcase))
          return 0;
        continue;
      case L'y':
        if (!_conv((t->tm_year + TM_YEAR_BASE) % 100, 2, pad))
          return 0;
        continue;
      case L'Y':
        if (!_conv(t->tm_year + TM_YEAR_BASE, 4, pad))
          return 0;
        continue;
      case L'z':
        if (!_add(t->__tm_gmtoff < 0 ? L"-" : L"+", 0))
          return 0;
        if (!_conv(t->__tm_gmtoff < 0 ? -t->__tm_gmtoff : t->__tm_gmtoff, 4, pad))
          return 0;
        continue;
      case L'Z':
        if (t->tm_zone)
        {
          mbstate_t mbs;
          wchar_t tm_zone[sizeof(t->tm_zone)];
          const char *zone;

          wcrtomb(NULL, L'\0', &mbs); /* initial shift state */
          zone = t->tm_zone;
          mbsrtowcs(tm_zone, &zone, sizeof(tm_zone)/sizeof(tm_zone[0]), &mbs);
          if (swap_case)
          {
            size_t i;
            upcase = 0;
            for (i = 0; tm_zone[i] != L'\0'; ++i)
              tm_zone[i] = towlower(tm_zone[i]);
          }
          if (!_add(tm_zone, upcase))
            return 0;
        }
        else
          return 0;
        continue;
      case L'+':
        /*
         *  The date and time in date(1) format.  An extension introduced
         *  with Olson's timezone package and still not supported.
         */
      case L'%':
        /*
         * X311J/88-090 (4.12.3.5): if conversion char is
         * undefined, behavior is undefined.  Print out the
         * character itself as printf(3) does.
         */
      default:
        break;
      }
    }
    if (!gsize--)
      return 0;
    *pt++ = *format;
  }
  return gsize;
}

size_t
wcsftime(wchar_t *s, size_t maxsize, const wchar_t *format, const struct tm *t)
{
  pt = s;
  if ((gsize = maxsize) < 1)
    return 0;
  if (_fmt(format, t, 0))
  {
    *pt = L'\0';
    return maxsize - gsize;
  }
  return 0;
}
