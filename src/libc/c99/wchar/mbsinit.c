/* Copyright 2020 Ray Chason. See COPYING.dj for details. */

#include <wchar.h>

int
mbsinit(const mbstate_t *ps)
{
    /* No supported encoding has non-initial shift states */
    return 1;
}
