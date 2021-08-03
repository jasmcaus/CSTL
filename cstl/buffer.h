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
#include <cstl/debug.h>
#include <cstl/types.h>

typedef struct cstlBuffer cstlBuffer;

struct cstlBuffer {
    char* data;    // buffer data
    UInt64 length; // buffer size
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
// Append `buff2` to the buffer data
static void buff_append(cstlBuffer* buffer, cstlBuffer* buff2);
// Assign `new_buff` to the buffer data
static void buff_set(cstlBuffer* buffer, char* new_buff);
// Reset a buffer
static void buff_reset(cstlBuffer* buffer);
// Reverse a buffer (non-destructive)
static cstlBuffer* buff_rev(cstlBuffer* buffer);
// Free the buffer from its associated memory
static void buff_free(cstlBuffer* buffer);

// Create a new `cstlBuffer`
static cstlBuffer* buff_new(char* buff_data) {
    cstlBuffer* buffer = (cstlBuffer*)calloc(1, sizeof(cstlBuffer));
    CSTL_CHECK_NOT_NULL(buffer, "Could not allocate memory. Memory full.");

    buff_set(buffer, buff_data);

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

// Append `buff2` to the buffer data
// Returns `buffer`
static void buff_append(cstlBuffer* buffer, cstlBuffer* buff2) {
    CSTL_CHECK_NOT_NULL(buffer, "Expected not null");
    CSTL_CHECK_NOT_NULL(buffer->data, "Expected not null");
    CSTL_CHECK_NOT_NULL(buff2, "Expected not null");
    CSTL_CHECK_NOT_NULL(buff2->data, "Expected not null");

    UInt64 new_len = buffer->length + buff2->length + 1;
    char* newstr = (char*)calloc(1, new_len);
    strcpy(newstr, buffer->data);
    strcat(newstr, buff2->data);
    buff_set(buffer, newstr);
}

// Append a character to the buffer data
static void buff_append_char(cstlBuffer* buffer, char ch) {
    CSTL_CHECK_NOT_NULL(buffer, "Expected not null");
    CSTL_CHECK_NOT_NULL(buffer->data, "Expected not null");

    UInt64 len = buffer->length;
    char* newstr = (char*)calloc(1, len + 1);
    strcpy(newstr, buffer->data);
    newstr[len] = ch;
    newstr[len + 1] = nullchar;
    buff_set(buffer, newstr);
    buffer->length += 2;
}

// Assign `new_buff` to the buffer data
static void buff_set(cstlBuffer* buffer, char* new_buff) {
    CSTL_CHECK_NOT_NULL(buffer, "Expected not null");

    UInt64 len;
    if(!new_buff) {
        len = 0;
        new_buff = "";
    } else {
        len = (UInt64)strlen(new_buff);
    }

    buffer->data = new_buff;
    buffer->length = len;
}

// Free the buffer from its associated memory
static void buff_reset(cstlBuffer* buffer) {
    if(buffer == null)
        return;

    buffer->data = null;
    buffer->length = 0;
}

// Reverse a buffer (non-destructive)
static Buff* buff_rev(Buff* buffer) {
    Buff* rev = buff_new(null);
    UInt64 length = buffer->length;
    if(!length)
        return rev;
    
    char* temp = (char*)calloc(1, length + 1);
    for(UInt64 i=0; i<length; i++)
        *(temp + i) = *(buffer->data + length - i - 1);
    
    buff_set(rev, temp);
    return rev;
}

// Free the buffer from its associated memory
static void buff_free(cstlBuffer* buffer) {
    free(buffer);
}

#endif // CSTL_BUFFER_H