/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#ifndef __dj_include_sys_attrib_h_
#define __dj_include_sys_attrib_h_

/* Mark a function as deprecated */
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
#   define __dj_attr_deprecated(msg) __attribute__((__deprecated__(msg)))
#elif __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)
#   define __dj_attr_deprecated(msg) __attribute__((__deprecated__))
#else
#   define __dj_attr_deprecated(msg)
#endif

/* Mark a function as unavailable */
#if __GNUC__ >= 12
#   define __dj_attr_unavailable(msg) __attribute__((__unavailable__(msg)))
#elif __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
#   define __dj_attr_unavailable(msg) __attribute__((__error__(msg)))
#else
#   define __dj_attr_unavailable(msg)
#endif

#endif
