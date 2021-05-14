/*
  ______ ____ ________ _
 / ____/ ____|__   __/| |
| |    | (_     | |   | |      CSTL - The neatest rewrite of the C/C++ Standard Library
| |    \___ \   | |   | |      Language: C
| |___ ____) |  | |   | |____  https://github.com/jasmcaus/CSTL
 \_____\_____/  |_|   \______| 

Licensed under the MIT License <http://opensource.org/licenses/MIT>
SPDX-License-Identifier: MIT
Copyright (c) 2021 Jason Dsouza <http://github.com/jasmcaus>
*/


#ifndef CSTL_OS_H
#define CSTL_OS_H

#ifdef __cplusplus
namespace cstl {
#endif


// Operating Systems ==========================================
// CSTL_OS_...
#if defined(_WIN32) || defined(_WIN64)
    #ifndef CSTL_OS_WINDOWS
        #define CSTL_OS_WINDOWS 1
    #endif

#elif defined(__APPLE__) && defined(__MACH__)
    #ifndef CSTL_OS_OSX
        #define CSTL_OS_OSX 1
    #endif

#elif defined(__unix__)
    #ifndef CSTL_OS_UNIX
        #define CSTL_OS_UNIX 1
    #endif

    #if defined(__linux__)
        #ifndef CSTL_OS_LINUX
            #define CSTL_OS_LINUX 1
        #endif
    
    #elif defined(__FreeBSD__) && defined(__FreeBSD_kernel__)
        #ifndef CSTL_OS_FREEBSD
            #define CSTL_OS_FREEBSD 1
        #endif

    #else 
        #error This Unix Operating System in not supported by Hazel.
    #endif 

#elif defined(__NetBSD__)
    #define CSTL_OS_NETBSD
    
#elif defined(__DragonFly__)
    #define CSTL_OS_DRAGONFLY
    
#elif defined(__OpenBSD__)
    #define CSTL_OS_OPENBSD
    
#elif defined(__HAIKU__)
    #define CSTL_OS_HAIKU

#else
    #error This Operating System in not supported by Hazel
#endif

// Architetures
#if defined(__x86_64__)
    #define CSTL_ARCH_X86_64
#elif defined(__aarch64__)
    #define CSTL_ARCH_ARM64
#elif defined(__ATM_EABI__)
    #define CSTL_ARCH_ARM
#else
    #error This Architecture is not supoorted by Hazel
#endif // __x86_64


// printf Format specifiers
#define CSTL_PRI_usize  "Iu"
#define CSTL_PRId64     "I64d"
#define CSTL_PRIu64     "I64u"
#define CSTL_PRI_x64    "I64x"

#ifdef CSTL_OS_WINDOWS
    #define CSTL_OS_SEP         "\\"
    #define CSTL_OS_SEP_CHAR    '\\'
#else
    #define CSTL_OS_SEP         "/"
    #define CSTL_OS_SEP_CHAR    '/'
#endif // CSTL_OS_WINDOWS


// Terminal Colours
typedef TerminalColours {
    CSTL_TERMCOLOUR_RED_,
    CSTL_TERMCOLOUR_GREEN_,
    CSTL_TERMCOLOUR_CYAN_,
    CSTL_TERMCOLOUR_WHITE_,
    CSTL_TERMCOLOUR_BOLD_,
    CSTL_TERMCOLOUR_RESET_,
} TerminalColours;

#ifdef __cplusplus
} // namespace cstl
#endif

#endif // CSTL_OS_H
