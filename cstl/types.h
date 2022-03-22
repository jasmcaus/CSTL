/*
          _____   ____  _____            _____
    /\   |  __ \ / __ \|  __ \     /\   |  __ \
   /  \  | |  | | |  | | |__) |   /  \  | |  | | Adorad - The Fast, Expressive & Elegant Programming Language
  / /\ \ | |  | | |  | |  _  /   / /\ \ | |  | | Languages: C, C++, and Assembly
 / ____ \| |__| | |__| | | \ \  / ____ \| |__| | https://github.com/adorad/adorad/
/_/    \_\_____/ \____/|_|  \_\/_/    \_\_____/

Licensed under the MIT License <http://opensource.org/licenses/MIT>
SPDX-License-Identifier: MIT
Copyright (c) 2021-22 Jason Dsouza <@jasmcaus>
*/

#ifndef CORETEN_TYPES_H
#define CORETEN_TYPES_H

// This macro is only for simple assertion checks (that don't require a message to STDOUT).
// If a condition fails, this raises a compilation error (negative index) --> 0*2 == 0 + (-1) == -1!
// Note that this macro is only for this file (<...>/core/types.h)
#define __CORETEN_STAT_ASSERT1(cond, line)      typedef char static_assertion_at_line_##line[(!!(cond))*2-1]
#define CORETEN_STATIC_ASSERT(cond)             __CORETEN_STAT_ASSERT1(cond, __LINE__)

//================================== Built-in types ================================*/
/*
    typedef unsigned char       UInt8; 
    typedef          char       Int8;  
    typedef unsigned short      UInt16;
    typedef signed short        Int16; 
    typedef unsigned int        UInt32;
    typedef signed int          Int32; 
    typedef unsigned long long  UInt64;
    typedef long long           Int64; 
    typedef float               Float32; 
    typedef double              Float64; 
*/
#if defined(CORETEN_COMPILER_MSVC)
    #if _MSVC_VER < 1300 
        typedef unsigned char     UInt8;
        typedef signed char       Int8;
        typedef unsigned short    UInt16;
        typedef signed short      Int16;
        typedef unsigned int      UInt32;
        typedef signed int        Int32;
    #else 
        typedef unsigned __int8   UInt8;
        typedef signed __int8     Int8;
        typedef unsigned __int16  UInt16;
        typedef signed __int16    Int16;
        typedef unsigned __int32  UInt32;
        typedef signed __int32    Int32;
    #endif 

    typedef unsigned __int64  UInt64; 
    typedef signed __int64    Int64;

#else 
    #ifdef __cplusplus
        #include <cstdint>
    #else
        #include <stdint.h>
    #endif // __cplusplus

    typedef uint8_t   UInt8; 
    typedef int8_t    Int8; 
    typedef uint16_t  UInt16; 
    typedef int16_t   Int16; 
    typedef uint32_t  UInt32; 
    typedef int32_t   Int32; 
    typedef uint64_t  UInt64; 
    typedef int64_t   Int64; 
#endif // Adorad Basic types

typedef char* charptr;
typedef void* voidptr;

typedef float  Float32;
typedef double Float64;

// Bool-sy
typedef Int8  Bool8; 
typedef Int16 Bool16;
typedef Int32 Bool32; // Prefer this!

CORETEN_STATIC_ASSERT(sizeof(UInt8)  == sizeof(Int8));
CORETEN_STATIC_ASSERT(sizeof(UInt16) == sizeof(Int16));
CORETEN_STATIC_ASSERT(sizeof(UInt32) == sizeof(Int32));
CORETEN_STATIC_ASSERT(sizeof(UInt64) == sizeof(Int64));

CORETEN_STATIC_ASSERT(sizeof(UInt8)  == 1);
CORETEN_STATIC_ASSERT(sizeof(UInt16) == 2);
CORETEN_STATIC_ASSERT(sizeof(UInt32) == 4);
CORETEN_STATIC_ASSERT(sizeof(UInt64) == 8);

CORETEN_STATIC_ASSERT(sizeof(Float32) == 4);
CORETEN_STATIC_ASSERT(sizeof(Float64) == 8);

CORETEN_STATIC_ASSERT(sizeof(Bool8)  == 1);
CORETEN_STATIC_ASSERT(sizeof(Bool16) == 2);
CORETEN_STATIC_ASSERT(sizeof(Bool32) == 4);

// Unicode codepoint
typedef UInt8  Byte;
typedef UInt32 Rune;
typedef unsigned char* Byteptr;

#define CORETEN_RUNE_INVALID cast(Rune)(0xfffd)
#define CORETEN_RUNE_MAX     cast(Rune)(0x0010ffff)
#define CORETEN_RUNE_BOM     cast(Rune)(0xfeff)
#define CORETEN_RUNE_EOF     cast(Rune)(-1)

CORETEN_STATIC_ASSERT(sizeof(Byte) == 1);
CORETEN_STATIC_ASSERT(sizeof(Rune) == 4);

// Max and Min 
#ifndef UInt8_MIN 
    #define UInt8_MIN 0u
    #define UInt8_MAX 0xffu
    #define Int8_MIN  (-0x7f - 1)
    #define Int8_MAX  0x7f

    #define UInt16_MIN 0u
    #define UInt16_MAX 0xffffu
    #define Int16_MIN  (-0x7fff - 1)
    #define Int16_MAX  0x7fff
 
    #define UInt32_MIN 0u
    #define UInt32_MAX 0xffffffffu
    #define Int32_MIN  (-0x7fffffff - 1)
    #define Int32_MAX  0x7fffffff

    #define UInt64_MIN 0ull
    #define UInt64_MAX 0xffffffffffffffffull
    #define Int64_MIN  (-0x7fffffffffffffffll - 1)
    #define Int64_MAX  0x7fffffffffffffffll

    #if defined(CORETEN_ARCH_32BIT)
        #define UINTSIZE_MIX UInt32_MIN
        #define UINTSIZE_MAX UInt32_MAX

        #define INTSIZE_MIX Int32_MIN
        #define INTSIZE_MAX Int32_MAX
    
    #elif defined(CORETEN_ARCH_64BIT)
        #define UINTSIZE_MIX UInt64_MIN
        #define UINTSIZE_MAX UInt64_MAX

        #define INTSIZE_MIX Int64_MIN
        #define INTSIZE_MAX Int64_MAX
    #endif 
#else
    #error AdoradError: Unknown architecture size. Adorad only supports 32-bit and 64-bit architectures.
#endif 

#define Float32_MIN 1.17549435e-38f
#define Float32_MAX 3.40282347e+38f

#define Float64_MIN 2.2250738585072014e-308
#define Float64_MAX 1.7976931348623157e+308

// The same thing as size_t 
// Ull --> size_t
// Ll  --> ptrdiff_t
#if defined(_MSC_VER)
    #if !defined(_WIN64)
        typedef unsigned int Ull;
        typedef int          Ll;
    #else 
        typedef UInt64  Ull;
        typedef Int64   Ll;
    #endif // _WIN64
#else
    typedef UInt64  Ull;
    typedef Int64   Ll;
#endif // _MSC_VER

// (U)Intptr is only here for semantic reasons really as this library will only support 32/64 bit OSes.
// Are there any modern OSes (not 16 bit) where Intptr != ptrdiff_t/Ll ?
#if defined(_WIN64)
    typedef signed    __int64    Intptr;
    typedef unsigned  __int64    UIntptr;
#elif defined(_WIN32)
    // To mark types changing their size, e.g. Intptr
    #ifndef _W64
        #if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
            #define _W64 __w64
        #else
            #define _W64
        #endif 
    #endif

    typedef _W64 signed int     Intptr;
    typedef _W64 unsigned int   UIntptr;
#else
    typedef  uintptr_t   UIntptr;
    typedef  intptr_t    Intptr;
#endif

CORETEN_STATIC_ASSERT(sizeof(UIntptr) == sizeof(Intptr));

// More Useful types
#define nullchar '\0' 
 
#ifndef null 
    #ifdef __cplusplus
        #if __cplusplus >= 201103L
            #define null    nullptr 
        #else 
            #define null    0
        #endif 
    #else 
        #define null    ((void*)0)
    #endif // __cplusplus
#endif 

// bool is a basic type in C++ and not C
#ifndef Bool_types_defined
#define Bool_types_defined
    #ifdef __cplusplus
        #define false  false
        #define true   true
    #else
        typedef Bool8 bool;
        static const bool false = 0;
        static const bool true = 1;
    #endif // __cplusplus   
#endif // Bool_types_defined

#endif // CORETEN_TYPES_H