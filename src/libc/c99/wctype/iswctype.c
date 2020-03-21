/* Copyright 2020 Ray Chason. See COPYING.DJ for details. */

#include <wctype.h>
#include "wcpriv.h"

int iswctype(wint_t wc, wctype_t desc)
{
    int is_type;

    switch (desc)
    {
    case __dj_wc_iswalnum:
        is_type = iswalnum(wc);
        break;

    case __dj_wc_iswalpha:
        is_type = iswalpha(wc);
        break;

    case __dj_wc_iswblank:
        is_type = iswblank(wc);
        break;

    case __dj_wc_iswcntrl:
        is_type = iswcntrl(wc);
        break;

    case __dj_wc_iswdigit:
        is_type = iswdigit(wc);
        break;

    case __dj_wc_iswgraph:
        is_type = iswgraph(wc);
        break;

    case __dj_wc_iswlower:
        is_type = iswlower(wc);
        break;

    case __dj_wc_iswprint:
        is_type = iswprint(wc);
        break;

    case __dj_wc_iswpunct:
        is_type = iswpunct(wc);
        break;

    case __dj_wc_iswspace:
        is_type = iswspace(wc);
        break;

    case __dj_wc_iswupper:
        is_type = iswupper(wc);
        break;

    case __dj_wc_iswxdigit:
        is_type = iswxdigit(wc);
        break;

    default:
        is_type = 0;
        break;
    }

    return is_type;
}
