/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <stdio.h>
#include <wchar.h>

wint_t
ungetwc(wint_t c, FILE *stream)
{
    if (stream->_wungetsize >= sizeof(stream->_wunget)/sizeof(stream->_wunget[0])) {
        return WEOF;
    }
    stream->_wunget[stream->_wungetsize++] = (wchar_t)c;
    return c;
}
