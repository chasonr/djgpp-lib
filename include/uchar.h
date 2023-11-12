/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#ifndef __dj_include_uchar_h_
#define __dj_include_uchar_h_

#include <sys/djtypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MBSTATE_T
__DJ_mbstate_t
#define _MBSTATE_T
#endif

#ifndef _SIZE_T
__DJ_size_t
#define _SIZE_T
#endif

#ifndef __cplusplus
typedef unsigned short int char16_t;
typedef unsigned int char32_t;
#endif

size_t mbrtoc16(char16_t * __restrict__ /*pc16*/,
                const char * __restrict__ /*s*/, size_t /*n*/,
                mbstate_t * __restrict__ /*ps*/);
size_t c16rtomb(char * __restrict__ /*s*/, char16_t /*c16*/,
                mbstate_t * __restrict__ /*ps*/);
size_t mbrtoc32(char32_t * __restrict__ /*pc32*/,
                const char * __restrict__ /*s*/, size_t /*n*/,
                mbstate_t * __restrict__ /*ps*/);
size_t c32rtomb(char * __restrict__ /*s*/, char32_t /*c32*/,
                mbstate_t * __restrict__ /*ps*/);

#ifdef __cplusplus
};
#endif

#endif /* __dj_include_uchar_h_ */
