/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <limits.h>
#include <stdio.h>
#include <wchar.h>
#include <libc/file.h>

wint_t
fputwc(wchar_t c, FILE *stream)
{
    stream->_flag |= _IOWIDE;

    char s[MB_LEN_MAX];
    size_t size = wcrtomb(s, c, &stream->_mbstate);
    if (size == (size_t)(-1)) {
        return WEOF;
    }
    for (size_t i = 0; i < size; ++i) {
        int rc = __putc(s[i], stream);
        if (rc < 0) {
            return WEOF;
        }
    }
    return c;
}
