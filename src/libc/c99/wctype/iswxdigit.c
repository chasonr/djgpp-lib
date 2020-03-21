/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */
#include <wctype.h>

int iswxdigit(wint_t c)
{
    /*
     * ISO C, 7.30.2.1.12: "The iswxdigit function tests for any wide character
     * that corresponds to a hexadecimal-digit character (as defined in
     * 6.4.4.1)."
     *
     * 6.4.4.1: "hexadecimal-digit: one of
     *               0 1 2 3 4 5 6 7 8 9
     *               a b c d e f
     *               A B C D E F"
     */
    return (L'0' <= c && c <= L'9')
        || (L'A' <= c && c <= L'F')
        || (L'a' <= c && c <= L'f');
}
