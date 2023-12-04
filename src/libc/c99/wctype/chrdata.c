/* Copyright 2023 Ray Chason. See COPYING.dj for details. */

#include <stdlib.h>
#include <wchar.h>
#include "chrdata.h"

static int compare_range(void const *key_, void const *val_);
static int compare_map(void const *key_, void const *val_);

/* Input is a character and an array of character ranges */
/* Returns nonzero if the character is in one of the ranges */
int
__dj_find_range(wint_t ch, const struct chr_range *ranges, size_t ranges_size)
{
    const struct chr_range *p = bsearch(&ch, ranges,
            ranges_size, sizeof(ranges[0]), compare_range);
    return p != NULL;
}

static int
compare_range(const void *key_, const void *val_)
{
    const wint_t *key = key_;
    const struct chr_range *val = val_;

    if (*key < val->first)
        return -1;
    if (*key > val->last)
        return +1;
    return 0;
}

wint_t
__dj_find_map(wint_t ch, const struct chr_map *map, size_t map_size)
{
    const struct chr_map *p = bsearch(&ch, map, map_size, sizeof(map[0]),
            compare_map);
    return p ? p->to : WEOF;
}

static int
compare_map(const void *key_, const void *val_)
{
    const wint_t *key = key_;
    const struct chr_map *val = val_;

    if (*key < val->from)
        return -1;
    if (*key > val->from)
        return +1;
    return 0;
}
