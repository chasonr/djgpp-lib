/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <stdio.h>
#include <wchar.h>
#include <libc/file.h>

int
fwide(FILE *fp, int mode)
{
    if ((fp->_flag & (_IOBYTE | _IOWIDE)) == 0) {
        if (mode > 0) {
            fp->_flag |= _IOWIDE;
        } else if (mode < 0) {
            fp->_flag |= _IOBYTE;
        }
    }

    if (fp->_flag & _IOWIDE) {
        return +1;
    } else if (fp->_flag & _IOBYTE) {
        return -1;
    } else {
        return 0;
    }
}
