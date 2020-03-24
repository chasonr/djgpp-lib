/* Copyright 2020 Ray Chason. See COPYING.dj for details. */

#ifndef CODEPAGE_H
#define CODEPAGE_H

/* in libc/ansi/locale/setlocal.c */
extern unsigned __dj_current_codepage;

struct char_conv {
    wchar_t const single_map[128];
};

struct char_conv const *__dj_get_conversion(void);
wint_t __dj_single_map(struct char_conv const *table, int ch);
int __dj_single_unmap(struct char_conv const *table, wchar_t ch);

#endif
