/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_inline_wctype_ha_
#define __dj_include_inline_wctype_ha_

/* C++ does not allow redefining C library functions as macros */
#ifndef __cplusplus

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) \
  || !defined(__STRICT_ANSI__) || defined(__cplusplus)

#define __dj_ISWALPHA	0x01
#define __dj_ISWCNTRL	0x02
#define __dj_ISWDIGIT	0x04
#define __dj_ISWLOWER	0x08
#define __dj_ISWPRINT	0x10
#define __dj_ISWPUNCT	0x20
#define __dj_ISWSPACE	0x40
#define __dj_ISWUPPER	0x80

extern const unsigned char __dj_wctype_flags[];

#define iswalnum(c) (__dj_wctype_flags[(int)(c)+1] & (__dj_ISWALPHA | __dj_ISWDIGIT))
#define iswalpha(c) (__dj_wctype_flags[(int)(c)+1] & __dj_ISWALPHA)
#define iswcntrl(c) (__dj_wctype_flags[(int)(c)+1] & __dj_ISWCNTRL)
#define iswdigit(c) (__dj_wctype_flags[(int)(c)+1] & __dj_ISWDIGIT)
#define iswgraph(c) ((__dj_wctype_flags[(int)(c)+1] & (__dj_ISWPRINT | __dj_ISWSPACE)) == __dj_ISWPRINT)
#define iswlower(c) (__dj_wctype_flags[(int)(c)+1] & __dj_ISWLOWER)
#define iswprint(c) (__dj_wctype_flags[(int)(c)+1] & __dj_ISWPRINT)
#define iswpunct(c) (__dj_wctype_flags[(int)(c)+1] & __dj_ISWPUNCT)
#define iswspace(c) (__dj_wctype_flags[(int)(c)+1] & __dj_ISWSPACE)
#define iswupper(c) (__dj_wctype_flags[(int)(c)+1] & __dj_ISWUPPER)

#endif /* (__STDC_VERSION__ >= 199901L) || !__STRICT_ANSI__ */

#endif /* __cplusplus */

#endif /* __dj_include_inline_wctype_ha_ */
