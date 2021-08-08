/*
  ______ ____ ________ _
 / ____/ ____|__   __/| |
| |    | (_     | |   | |      CSTL - The neatest rewrite of the C/C++ Standard Library
| |    \___ \   | |   | |      Languages: C, C++ and Assembly
| |___ ____) |  | |   | |____  https://github.com/jasmcaus/cstl
 \_____\_____/  |_|   \______| 

Licensed under the MIT License <http://opensource.org/licenses/MIT>
SPDX-License-Identifier: MIT
Copyright (c) 2021 Jason Dsouza <@jasmcaus>
*/

#ifndef CSTL_ENDIAN_H_
#define CSTL_ENDIAN_H_

#include <cstl/types.h>

#if defined(__APPLE__)
    #include <machine/endian.h>
    #define CSTL_BIG_ENDIAN    BIG_ENDIAN
    #define CSTL_LITTLE_ENDIAN LITTLE_ENDIAN
    #define CSTL_BYTE_ORDER    BYTE_ORDER
#elif defined(__DragonFly__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
    #include <sys/endian.h>
    #define CSTL_BIG_ENDIAN    _BIG_ENDIAN
    #define CSTL_LITTLE_ENDIAN _LITTLE_ENDIAN
    #define CSTL_BYTE_ORDER    _BYTE_ORDER
#elif defined(_WIN32) || defined(_WIN64)
    // Assume that Windows installations are always little endian.
    #define CSTL_LITTLE_ENDIAN 1
    #define CSTL_BYTE_ORDER    CSTL_LITTLE_ENDIAN
#else // Linux
    #include <endian.h>
    #define CSTL_BIG_ENDIAN    __BIG_ENDIAN
    #define CSTL_LITTLE_ENDIAN __LITTLE_ENDIAN
    #define CSTL_BYTE_ORDER    __BYTE_ORDER
#endif

#if defined(CSTL_BYTE_ORDER) && CSTL_BYTE_ORDER == CSTL_LITTLE_ENDIAN
    #define NATIVE_IS_BIG_ENDIAN    0
#elif defined(CSTL_BYTE_ORDER) && CSTL_BYTE_ORDER == CSTL_BIG_ENDIAN
    #define NATIVE_IS_BIG_ENDIAN    1
#else
    #error AdoradError: Unsupported endianness
#endif

static inline UInt16 endian_swap16(UInt16 i);
static inline UInt32 endian_swap32(UInt32 i);
static inline UInt64 endian_swap64(UInt64 i);

#endif // CSTL_ENDIAN_H_