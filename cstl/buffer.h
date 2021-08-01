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

#ifndef CSTL_BUFFER_H
#define CSTL_BUFFER_H

#include <string.h>
#include <cstl/types.h>
#include <cstl/debug.h>

typedef struct cstlBuffer cstlBuffer;

struct cstlBuffer {
    char* data;    // buffer data
    UInt64 length; // buffer size


    char (*at)(cstlBuffer*, UInt64);
    // Front and back iterators
    char* (*begin)(cstlBuffer*);
    char* (*end)(cstlBuffer*);
    bool (*is_empty)(cstlBuffer*);
    // Buffer things
    void (*set)(cstlBuffer*, char*);
    void(*free)(cstlBuffer*);

};

// Create a new `cstlBuffer`
static cstlBuffer* buff_new(char* buff_data);
// Return the n'th character in the buffer data
static char buff_at(cstlBuffer* buffer, UInt64 n);
// Return a pointer to the beginning of the buffer data
static char* buff_begin(cstlBuffer* buffer);
// Return a pointer to the end of the buffer data
static char* buff_end(cstlBuffer* buffer);
// Is the buffer data empty?
static bool buff_is_empty(cstlBuffer* buffer);
// Assign `new` to the buffer data
static void buff_set(cstlBuffer* buffer, char* new_buff);
// Free the cstlBuffer from it's associated memory
static void buff_free(cstlBuffer* buffer);

// Create a new `cstlBuffer`
static cstlBuffer* buff_new(char* buff_data) {
    cstlBuffer* buffer = (cstlBuffer*)calloc(1, sizeof(cstlBuffer));
    CSTL_CHECK_NOT_NULL(buffer, "Could not allocate memory. Memory full.");

    UInt64 len;
    if(buff_data == null) {
        len = 0;
    } else {
        len = (UInt64)strlen(buff_data);
    }

    buffer->data = buff_data;
    buffer->length = len;


    buffer->at = &buff_at;
    buffer->begin = &buff_begin;
    buffer->end = &buff_end;
    buffer->is_empty = &buff_is_empty;
    buffer->set = &buff_set;
    buffer->free = &buff_free;


    return buffer;
}

// Return the n'th character in the buffer data
static char buff_at(cstlBuffer* buffer, UInt64 n) {
    CSTL_CHECK_NOT_NULL(buffer, "Expected not null");
    CSTL_CHECK_NOT_NULL(buffer->data, "Expected not null");
    
    if(n >= buffer->length)
        return nullchar;

    return (char)buffer->data[n];
}

// Return a pointer to the beginning of the buffer data
static char* buff_begin(cstlBuffer* buffer) {
    CSTL_CHECK_NOT_NULL(buffer, "Expected not null");
    CSTL_CHECK_NOT_NULL(buffer->data, "Expected not null");

    return (char*)buffer->data;
}

// Return a pointer to the end of the buffer data
static char* buff_end(cstlBuffer* buffer) {
    CSTL_CHECK_NOT_NULL(buffer, "Expected not null");
    CSTL_CHECK_NOT_NULL(buffer->data, "Expected not null");

    return (char*)(buffer->data + ((buffer->length - 1) * sizeof(char)));
}

// Is the buffer data empty?
static bool buff_is_empty(cstlBuffer* buffer) {
    CSTL_CHECK_NOT_NULL(buffer, "Expected not null");
    CSTL_CHECK_NOT_NULL(buffer->data, "Expected not null");

    return buffer->length == 0;
}

// Assign `new` to the buffer data
static void buff_set(cstlBuffer* buffer, char* new_buff) {
    CSTL_CHECK_NOT_NULL(buffer, "Expected not null");

    buffer->data = new_buff;
    buffer->length = (UInt64)strlen(new_buff);
}

// Free the cstlBuffer from it's associated memory
static void buff_free(cstlBuffer* buffer) {
    if(buffer == null)
        return;

    buffer->data = null;
    buffer->length = 0;
}

#endif // CSTL_BUFFER_H