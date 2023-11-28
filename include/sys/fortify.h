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

/*
 * Macros for defining fortified functions
 * We call __foo_alias if we can verify, at compile time, that the length is
 * in bounds.
 * If the length is known not to be in bounds, we call __foo_chk_warn.
 * Otherwise, we call __foo_chk.
 */
/* Pass the object size */
#define __dj_fortify(function, length, elem_size, obj_size, ...) \
    ((((__typeof(length))0 < (__typeof(length))-1) || (__builtin_constant_p(length) && (length) >= 0)) \
    &&  __builtin_constant_p((length) <= (obj_size)/(elem_size))) \
    ? ( ((length) <= (obj_size)/(elem_size)) \
        ? __ ## function ## _alias(__VA_ARGS__) \
        : __ ## function ## _chk_warn(__VA_ARGS__, (obj_size)) ) \
    : __ ## function ## _chk(__VA_ARGS__, (obj_size))

/* Pass the number of elements in the array */
#define __dj_fortify_n(function, length, elem_size, obj_size, ...) \
    ((((__typeof(length))0 < (__typeof(length))-1) || (__builtin_constant_p(length) && (length) >= 0)) \
    &&  __builtin_constant_p((length) <= (obj_size)/(elem_size))) \
    ? ( ((length) <= (obj_size)/(elem_size)) \
        ? __ ## function ## _alias(__VA_ARGS__) \
        : __ ## function ## _chk_warn(__VA_ARGS__, (obj_size)/(elem_size)) ) \
    : __ ## function ## _chk(__VA_ARGS__, (obj_size)/(elem_size))

/* Forward a function all to a different name */
/* The two stringify macros are needed to make the prefix work properly */
#define __dj_stringify2(a) #a
#define __dj_stringify(a) __dj_stringify2(a)
#define __dj_forward(name) __asm__(__dj_stringify(__USER_LABEL_PREFIX__) __dj_stringify(name))

#endif /* __dj_include_sys_fortify_h_ */
