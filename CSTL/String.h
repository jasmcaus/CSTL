/*
  ______ ____ ________ _
 / ____/ ____|__   __/| |
| |    | (_     | |   | |      CSTL - The neatest rewrite of the C/C++ Standard Library
| |    \___ \   | |   | |      Languages: C, C++ and Assembly
| |___ ____) |  | |   | |____  https://github.com/jasmcaus/CSTL
 \_____\_____/  |_|   \______| 

Licensed under the MIT License <http://opensource.org/licenses/MIT>
SPDX-License-Identifier: MIT
Copyright (c) 2021 Jason Dsouza <http://github.com/jasmcaus>
*/

#ifndef CSTL_STRING_H
#define CSTL_STRING_H

#include <CSTL/Types.h>
#include <CSTL/Math.h>

// UTF8 Inspiration: https://github.com/sheredom/utf8.h/blob/master/utf8.h

#ifdef __cplusplus
namespace cstl {
#endif


// Char Things ==========================================
CSTL_STATIC CSTL_INLINE bool isUpper(char c) { return c>='A' && c<='Z'; }
CSTL_STATIC CSTL_INLINE bool isLower(char c) { return c>='a' && c<='z'; }
CSTL_STATIC CSTL_INLINE bool isDigit(char c) { return c >= '0' && c <= '9'; }
CSTL_STATIC CSTL_INLINE bool isAlpha(char c) { return isUpper(c) || isLower(c); }
CSTL_STATIC CSTL_INLINE bool isAlphanumeric(char c) { return isAlpha(c) || isDigit(c); }

CSTL_STATIC CSTL_INLINE char toLower(char c) {
    if(c >= 'A' && c <= 'Z') 
        return 'a' + (c - 'A');
    return c;
}

CSTL_STATIC CSTL_INLINE char toUpper(char c) {
    if(c >= 'a' && c <= 'z') 
        return 'A' + (c - 'a');
    return c;
}

CSTL_STATIC CSTL_INLINE bool isWhitespace(char c) {
    if(c == ' '  || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')
        return true; 
    return false;
}

CSTL_STATIC CSTL_INLINE bool isLetter(char c) {
    return  (c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            (c == '_') ;
}

CSTL_STATIC CSTL_INLINE bool isHexDigit(char c) {
    return isDigit(c)                   ||
           CSTL_IS_BETWEEN(c, 'a', 'f') ||
           CSTL_IS_BETWEEN(c, 'A', 'F'); 
}

CSTL_STATIC CSTL_INLINE Int32 digitToInt(char c) { return isDigit(c) ? c-'0' : c-'W'; }

CSTL_STATIC CSTL_INLINE Int32 hexDigitToInt(char c) {
    if(isDigit(c))
        return digitToInt(c);

    else if(CSTL_IS_BETWEEN(c, 'a', 'f'))
        return c-'a' + 10; 

    else if(CSTL_IS_BETWEEN(c, 'A', 'F'))
        return c-'A' + 10; 

    return -1; 
}

CSTL_STATIC CSTL_INLINE void strToLower(char* str) {
    if(!str) return; 
    while(*str) {
        *str = toLower(*str);
        str++;
    }
}

CSTL_STATIC CSTL_INLINE void strToUpper(char* str) {
    if(!str) return; 
    while(*str) {
        *str = toUpper(*str);
        str++;
    }
}

#ifdef __cplusplus
} // namespace cstl
#endif


#endif // CSTL_STRING_H
