/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <stdio.h>
#include <wchar.h>

int
fputws(const wchar_t * restrict s, FILE * restrict stream)
{
    for (size_t i = 0; s[i] != 0; ++i) {
        wint_t rc = fputwc(s[i], stream);
        if (rc == WEOF) {
            return WEOF;
        }
    }
    return 1;
}
