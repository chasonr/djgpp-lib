/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#ifndef __dj_include_sys_fortify_h_
#define __dj_include_sys_fortify_h_

#undef __DJ_USE_FORTIFY_LEVEL
#if defined(_FORTIFY_SOURCE) && (_FORTIFY_SOURCE) > 0 && defined(__OPTIMIZE__) && (__OPTIMIZE__) > 0

#   if _FORTIFY_SOURCE >= 3 && __GCC_VERSION__ >= 12
#       define __DJ_USE_FORTIFY_LEVEL 3
#   elif _FORTIFY_SOURCE >= 2
#       define __DJ_USE_FORTIFY_LEVEL 2
#   elif _FORTIFY_SOURCE >= 1
#       define __DJ_USE_FORTIFY_LEVEL 1
#   endif

#define __dj_fortify_function extern __inline __attribute__((__always_inline__)) \
            __attribute__((__gnu_inline__)) __attribute__((__artificial__))

#endif

#ifndef __DJ_USE_FORTIFY_LEVEL
#   define __DJ_USE_FORTIFY_LEVEL 0
#endif

/* Builtin object size macro */
#if __DJ_USE_FORTIFY_LEVEL >= 3
#   define __dj_bos(ptr, type) __builtin_dynamic_object_size(ptr, type)
#else
#   define __dj_bos(ptr, type) __builtin_object_size(ptr, type)
#endif

#endif /* __dj_include_sys_fortify_h_ */
