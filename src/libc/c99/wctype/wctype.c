/* Copyright 2020 Ray Chason. See COPYING.DJ for details. */

#include <wctype.h>
#include "string.h"
#include "wcpriv.h"

wctype_t wctype(const char *property)
{
    if (strcmp(property, "alnum") == 0)
        return __dj_wc_iswalnum;
    if (strcmp(property, "alpha") == 0)
        return __dj_wc_iswalpha;
    if (strcmp(property, "blank") == 0)
        return __dj_wc_iswblank;
    if (strcmp(property, "cntrl") == 0)
        return __dj_wc_iswcntrl;
    if (strcmp(property, "digit") == 0)
        return __dj_wc_iswdigit;
    if (strcmp(property, "graph") == 0)
        return __dj_wc_iswgraph;
    if (strcmp(property, "lower") == 0)
        return __dj_wc_iswlower;
    if (strcmp(property, "print") == 0)
        return __dj_wc_iswprint;
    if (strcmp(property, "punct") == 0)
        return __dj_wc_iswpunct;
    if (strcmp(property, "space") == 0)
        return __dj_wc_iswspace;
    if (strcmp(property, "upper") == 0)
        return __dj_wc_iswupper;
    if (strcmp(property, "xdigit") == 0)
        return __dj_wc_iswxdigit;

    return 0;
}
