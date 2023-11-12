/* Copyright 2020, 2023 Ray Chason. See COPYING.dj for details. */

#include <wchar.h>

int
mbsinit(const mbstate_t *ps)
{
    return ps == NULL || (ps->_num_bytes == 0 && ps->_surrogate == 0);
}
