/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <stdio.h>
#include <wchar.h>

wint_t
getwc(FILE *stream)
{
    return fgetwc(stream);
}
