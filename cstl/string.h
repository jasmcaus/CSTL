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

#ifndef CSTL_STRING_H
#define CSTL_STRING_H

#include <cstl/types.h>
#include <cstl/math.h>
#include <cstl/debug.h>
#include <stdlib.h> // for exit(1)

// UTF8 Inspiration: https://github.com/sheredom/utf8.h/blob/master/utf8.h

// Char Things ==========================================
static inline bool isUpper(char c) { return c>='A' && c<='Z'; }
static inline bool isLower(char c) { return c>='a' && c<='z'; }
static inline bool isDigit(char c) { return c >= '0' && c <= '9'; }
static inline bool isAlpha(char c) { return isUpper(c) || isLower(c); }
static inline bool isAlphanumeric(char c) { return isAlpha(c) || isDigit(c); }

static inline bool isOctalDigit(char c) {
    return CSTL_IS_BETWEEN(c, '0', '7');
}

static inline bool isBinaryDigit(char c) {
    return c == '0' || c == '1';
}

static inline bool isHexDigit(char c) {
    return isDigit(c)                   ||
           CSTL_IS_BETWEEN(c, 'a', 'f') ||
           CSTL_IS_BETWEEN(c, 'A', 'F'); 
}


static inline bool isLetter(char c) {
    return  (c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            (c == '_') ;
}

static inline char toLower(char c) {
    if(c >= 'A' && c <= 'Z') 
        return 'a' + (c - 'A');
    return c;
}

static inline char toUpper(char c) {
    if(c >= 'a' && c <= 'z') 
        return 'A' + (c - 'a');
    return c;
}

static inline bool isWhitespace(char c) {
    if(c == ' '  || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')
        return true; 
    return false;
}

static inline Int32 digitToInt(char c) { return isDigit(c) ? c-'0' : c-'W'; }

static inline Int32 hexDigitToInt(char c) {
    if(isDigit(c))
        return digitToInt(c);

    else if(CSTL_IS_BETWEEN(c, 'a', 'f'))
        return c-'a' + 10; 

    else if(CSTL_IS_BETWEEN(c, 'A', 'F'))
        return c-'A' + 10; 

    return -1; 
}

static inline void strToLower(char* str) {
    if(!str) return; 
    while(*str) {
        *str = toLower(*str);
        str++;
    }
}

static inline void strToUpper(char* str) {
    if(!str) return; 
    while(*str) {
        *str = toUpper(*str);
        str++;
    }
}

// Get a substring from `source` and copies it into `destination`
static inline void substr(char* destination, char const* source, int begin, int bytes) {
    CSTL_CHECK_NOT_NULL(destination, "`destination` cannot be null. Did you forget to allocate memory for it?");
    CSTL_CHECK_NOT_NULL(source, "`source` cannot be null");
    CSTL_CHECK_GE(begin, 0);
    strncpy(destination, &(source[begin]), bytes);
}

#endif // CSTL_STRING_H