/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <stdio.h>
#include <wchar.h>
#include <libc/file.h>

wint_t
ungetwc(wint_t c, FILE *stream)
{
    if (stream->_flag & _IOSTRG) {
        if (stream->_ptr < stream->_base + sizeof(wchar_t)) {
            return WEOF;
        }
        stream->_ptr -= sizeof(wchar_t);
        /* Don't write; the buffer may be in non-writable memory */
    } else {
        if (stream->_wungetsize >= sizeof(stream->_wunget)/sizeof(stream->_wunget[0])) {
            return WEOF;
        }
        stream->_wunget[stream->_wungetsize++] = (wchar_t)c;
    }
    return c;
}
