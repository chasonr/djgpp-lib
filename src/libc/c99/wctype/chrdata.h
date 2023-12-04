/* Copyright 2020, 2023 Ray Chason. See COPYING.dj for details. */

#ifndef CHRDATA_H
#define CHRDATA_H

#include <wchar.h>

struct chr_range {
    wint_t first;
    wint_t last;
};

struct chr_map {
    wint_t from;
    wint_t to;
};

extern int __dj_find_range(wint_t ch, const struct chr_range *ranges, size_t ranges_size);
extern wint_t __dj_find_map(wint_t ch, const struct chr_map *map, size_t map_size);

#endif
