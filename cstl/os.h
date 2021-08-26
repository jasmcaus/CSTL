/*
          _____   ____  _____            _____
    /\   |  __ \ / __ \|  __ \     /\   |  __ \
   /  \  | |  | | |  | | |__) |   /  \  | |  | | Adorad - The Fast, Expressive & Elegant Programming Language
  / /\ \ | |  | | |  | |  _  /   / /\ \ | |  | | Languages: C, C++, and Assembly
 / ____ \| |__| | |__| | | \ \  / ____ \| |__| | https://github.com/adorad/adorad/
/_/    \_\_____/ \____/|_|  \_\/_/    \_\_____/

Licensed under the MIT License <http://opensource.org/licenses/MIT>
SPDX-License-Identifier: MIT
Copyright (c) 2021 Jason Dsouza <@jasmcaus>
*/

#ifndef CORETEN_OS_H
#define CORETEN_OS_H

#include <cstl/buffer.h>
#include <cstl/os_defs.h>
#include <cstl/types.h>

#if defined(CORETEN_OS_POSIX)
    #define _XOPEN_SOURCE 700
    #include <unistd.h>
#endif // CORETEN_OS_POSIX

#if defined(CORETEN_OS_WINDOWS)
    #include <direct.h>
#endif // CORETEN_OS_WINDOWS

cstlBuffer* os_get_cwd();
cstlBuffer* os_path_dirname(cstlBuffer* path);
cstlBuffer* os_path_extname(cstlBuffer* path);
cstlBuffer* os_path_join(cstlBuffer* path1, cstlBuffer* path2);
bool os_is_sep(char ch);
bool os_path_is_abs(cstlBuffer* path);
bool os_path_is_rel(cstlBuffer* path);
bool os_path_is_root(cstlBuffer* path);

#ifndef CORETEN_OS_FUNC_ALIASES
    #define CORETEN_OS_FUNC_ALIASES
    #define ospd    os_path_dirname
    #define ospb    os_path_basename
    #define ospj    os_path_join
#endif // CORETEN_OS_FUNC_ALIASES

#endif // CORETEN_OS_H