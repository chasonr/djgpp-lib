/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <stdio.h>
#include <wchar.h>

wchar_t *
fgetws(wchar_t * restrict s, int n, FILE * restrict stream)
{
    if (n <= 0) {
        return NULL;
    }

    int i;
    for (i = 0; i+1 < n; ++i) {
        wint_t wch = fgetwc(stream);
        if (wch == WEOF) {
            if (feof(stream)) {
                break;
            }
            return NULL;
        }
        s[i] = (wchar_t)wch;
        if (wch == L'\n') {
            ++i;
            break;
        }
    }
    s[i] = L'\0';
    return s;
}
