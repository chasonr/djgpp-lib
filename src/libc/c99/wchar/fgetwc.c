/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <stdio.h>
#include <wchar.h>
#include <libc/file.h>

wint_t
fgetwc(FILE *stream)
{
    stream->_flag |= _IOWIDE;

    wchar_t wch;

    /* Input of a supplementary character may have left a surrogate in the
       multibyte state */
    size_t size = mbrtowc(&wch, "", 0, &stream->_mbstate);
    if (size == (size_t)(-3)) {
        return wch;
    }

    /* Read from _wunget if available */
    if (stream->_wungetsize != 0) {
        return stream->_wunget[--stream->_wungetsize];
    }

    while (1) {
        int ch = __getc(stream);
        if (ch < 0) {
            return WEOF;
        }
        char s = (char)ch;
        size = mbrtowc(&wch, &s, 1, &stream->_mbstate);
        if (size == (size_t)(-1)) {
            return WEOF;
        }
        if (size != (size_t)(-2)) {
            break;
        }
    }

    return wch;
}
