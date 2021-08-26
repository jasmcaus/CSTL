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

#include <string.h>
#include <stdlib.h>
#include <coreten/os.h>
#include <coreten/debug.h>

cstlBuffer* os_get_cwd() {
#if defined(CORETEN_OS_WINDOWS)
    // This (or its equivalent) is not defined in any include in Windows as far as I've come across
    #define PATH_MAX 4096
    char result[PATH_MAX];
    _getcwd(result, PATH_MAX);
    if(!*result) {
        fprintf(stderr, "Unable to `os_get_cwd()`. 'getcwd()' failed");
        exit(1);
    }
    cstlBuffer* buff = buff_new(result);
    return buff;
#elif defined(CORETEN_OS_POSIX)
    long n;
    char *buf;

    n = pathconf(".", _PC_PATH_MAX);
    CORETEN_ENFORCE(n != -1);
    buf = cast(char*)calloc(n, sizeof(*buf));
    CORETEN_ENFORCE_NN(buf, "calloc failed. Out of memory");
    char* result = getcwd(buf, n);
    if(!result) {
        fprintf(stderr, "Unable to `os_get_cwd()`. 'getcwd()' failed");
        exit(1);
    }
    cstlBuffer* buff = buff_new(buf);
    return buff;
#else
    #error "No `os_get_cwd()` implementation supported for your platform."
    return null;
#endif // CORETEN_OS_WINDOWS
}

cstlBuffer* __os_dirname_basename(cstlBuffer* path, bool is_basename) {
    UInt64 length = path->len;
    if(!length)
        return path;

    cstlBuffer* result = buff_new(null);
    char* end = buff_end(path);

    // dirname
    if(!is_basename) {
        cstlBuffer* rev = buff_rev(path);

        // The `/` or `\\` is not so important in getting the dirname, but it does interfere with `strchr`, so
        // we skip over it (if present)
        if(*rev->data == CORETEN_OS_SEP_CHAR)
            rev->data++;
        char* rev_dir = strchr(rev->data, CORETEN_OS_SEP_CHAR);
        buff_set(result, rev_dir);
        result = buff_rev(result);
        buff_free(rev);
    } 

    // basename
    else {
        // If the last character is a `sep`, `basename` is empty
        if(os_is_sep(*end))
            return buff_new(null);
        
        // If there is no `sep` in `path`, `path` is the basename
        if(!(strstr(path->data, "/") || strstr(path->data, "\\")))
            return path;
        
        cstlBuffer* rev = buff_rev(path);
        for(UInt64 i = 0; i<length; i++) {
            if(os_is_sep(*(rev->data + i))) {
                *(rev->data + i) = nullchar;
                break;
            }
        }
        buff_set(result, rev->data);
        result = buff_rev(result);
        buff_free(rev);
    }
    
    return result;
}

cstlBuffer* os_path_dirname(cstlBuffer* path) {
    return __os_dirname_basename(path, false);
}

cstlBuffer* os_path_basename(cstlBuffer* path) {
    return __os_dirname_basename(path, true);
}

cstlBuffer* os_path_extname(cstlBuffer* path) {
    cstlBuffer* basename = os_path_basename(path);
    if(!strcmp(basename->data, ""))
        return basename;
    
    char* ext = strchr(basename->data, '.');
    if(!ext) {
       free(basename);
       return buff_new(null);
    }

    buff_set(basename, ext);
    return basename;
}

cstlBuffer* os_path_join(cstlBuffer* path1, cstlBuffer* path2) {
    UInt64 length = path1->len;
    if(!length)
        return path1;
        
    char* end = buff_end(path1);
    if(!os_is_sep(*end))
        buff_append_char(path1, CORETEN_OS_SEP_CHAR);
    buff_append(path1, path2);
    return path1;
}

bool os_is_sep(char ch) {
#ifdef CORETEN_OS_WINDOWS
    return ch == '\\' || ch == '/';
#else
    return ch == '/';
#endif // CORETEN_OS_WINDOWS
}

bool os_path_is_abs(cstlBuffer* path) {
    bool result = false;
    CORETEN_ENFORCE_NN(path, "Cannot do anything useful on a null path :(");
#ifdef CORETEN_OS_WINDOWS
	// The 'C:\...`
    result = path->len > 2 &&
             char_is_alpha(path->data[0]) &&
             (path->data[1] == ':' && path->data[2] == CORETEN_OS_SEP_CHAR);
#else
	result = path->len > 2 &&
			 path->data[0] == CORETEN_OS_SEP_CHAR;
#endif // CORETEN_OS_WINDOWS
	return cast(bool)result;
}

bool os_path_is_rel(cstlBuffer* path) {
	return cast(bool) !os_path_is_abs(path);
}

bool os_path_is_root(cstlBuffer* path) {
	bool result = false;
	CORETEN_ENFORCE_NN(path, "Cannot do anything useful on a null path :(");
#ifdef CORETEN_OS_WINDOWS
    result = os_path_is_abs(path) && path->len == 3;
#else
    result = os_path_is_abs(path) && path->len == 1;
#endif // CORETEN_OS_WINDOWS
	return result;
}