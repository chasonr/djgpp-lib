/* Copyright 2020, 2023 Ray Chason. See COPYING.dj for details. */

#ifndef CODEPAGE_H
#define CODEPAGE_H

#include <sys/djtypes.h>

#ifndef _WCHAR_T
__DJ_wchar_t
#define _WCHAR_T
#endif

#ifndef _WINT_T
__DJ_wint_t
#define _WINT_T
#endif

/* Code page 65001 is UTF-8 in Windows; make it so here as well */
#define UTF8_CODEPAGE 65001

/* in libc/ansi/locale/setlocal.c */
extern unsigned __dj_current_codepage;
extern int __dj_c_locale;

struct char_conv {
    wchar_t const single_map[128];
};

struct char_conv const *__dj_get_conversion(void);
wint_t __dj_single_map(struct char_conv const *table, int ch);
int __dj_single_unmap(struct char_conv const *table, wchar_t ch);
int __dj_is_utf8(void);

#endif
