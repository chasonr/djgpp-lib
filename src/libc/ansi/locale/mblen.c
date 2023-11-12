/* Copyright (C) 2020, 2023 Ray Chason, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdlib.h>
#include <wchar.h>
#include "../../c99/wchar/codepage.h"

int
mblen(const char *s, size_t n)
{
  unsigned char ch;
  wint_t wc;
  if (s)
  {
    if (n == 0)
      return -1;
    ch = (unsigned char)s[0];
    if (ch == 0)
      return 0;
    if (__dj_is_utf8()) {
      /* Check for valid UTF-8 */
      ch = s[0];
      if (ch < 0x80) {
        /* Single byte character */
        return 1;
      } else if (ch < 0xC2) {
        /* Stray continuation byte or overlong encoding */
        return -1;
      } else if (ch < 0xE0) {
        /* Two byte character */
        if (n < 2) {
          return -1;
        }
        ch = (unsigned char)s[1];
        if (0x80 <= ch && ch <= 0xBF) {
          return 2;
        } else {
          return -1;
        }
      } else if (ch < 0xF0) {
        /* Three byte character */
        if (n < 3) {
          return -1;
        }
        unsigned char ch2 = (unsigned char)s[1];
        if (ch2 < 0x80 || 0xBF < ch2) {
          /* Invalid continuation byte */
          return -1;
        }
        if (ch == 0xE0 && ch2 < 0xA0) {
          /* Overlong encoding */
          return -1;
        }
        if (ch == 0xED && ch2 > 0x9F) {
          /* Surrogate code point */
          return -1;
        }
        ch2 = (unsigned char)s[2];
        if (ch2 < 0x80 || 0xBF < ch2) {
          /* Invalid continuation byte */
          return -1;
        }
        return 3;
      } else if (ch < 0xF5) {
        /* Four byte character */
        if (n < 4) {
          return -1;
        }
        unsigned char ch2 = (unsigned char)s[1];
        if (ch2 < 0x80 || 0xBF < ch2) {
          /* Invalid continuation byte */
          return -1;
        }
        if (ch == 0xF0 && ch2 < 0x90) {
          /* Overlong encoding */
          return -1;
        }
        if (ch == 0xF4 && ch2 > 0x8F) {
          /* Invalid code point */
          return -1;
        }
        ch2 = (unsigned char)s[2];
        if (ch2 < 0x80 || 0xBF < ch2) {
          /* Invalid continuation byte */
          return -1;
        }
        ch2 = (unsigned char)s[3];
        if (ch2 < 0x80 || 0xBF < ch2) {
          /* Invalid continuation byte */
          return -1;
        }
        return 4;
      } else {
        return -1;
      }
    } else {
      wc = btowc(ch);
      if (wc == WEOF)
        return -1;
      return 1;
    }
  }
  else
    return 0;
}
