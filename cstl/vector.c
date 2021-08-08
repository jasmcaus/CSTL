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

#include <cstl/vector.h>

// Create a new `cstlVector`
// size = size of each element (in bytes)
// capacity = number of elements
cstlVector* _vec_new(UInt64 objsize, UInt64 capacity) {
    if(capacity == 0)
        capacity = VEC_INIT_ALLOC_CAP;
    
    cstlVector* vec = cast(cstlVector*)calloc(1, sizeof(cstlVector));
    CHECK_NOT_NULL(vec, "Could not allocate memory. Memory full.");

    vec->internal.data = cast(void*)calloc(objsize, capacity);
    if(!vec->internal.data) {
        free(vec);
        CHECK_NOT_NULL(vec->internal.data, "Could not allocate memory. Memory full.");
    }

    vec->internal.capacity = capacity;
    vec->internal.size = 0;
    vec->internal.objsize = objsize;

    return vec;
} 

// Free a cstlVector from it's associated memory
void vec_free(cstlVector* vec) {
    if(vec) {
        if(vec->internal.data)
            free(vec->internal.data);
        free(vec);
    }
}

// Return a pointer to element `i` in `vec`
void* vec_at(cstlVector* vec, UInt64 elem) {
    CHECK_NOT_NULL(vec, "Expected not null");
    CHECK_NOT_NULL(vec->internal.data, "Expected not null");

    if(elem > vec->internal.size)
        return null;

    return VECTOR_AT_MACRO(vec, elem);
}

// Return a pointer to first element in `vec`
void* vec_begin(cstlVector* vec) {
    CHECK_NOT_NULL(vec, "Expected not null");
    CHECK_NOT_NULL(vec->internal.data, "Expected not null");

    if(vec->internal.size == 0) 
        return null;
    
    return vec->internal.data;
}

// Return a pointer to last element in `vec`
void* vec_end(cstlVector* vec) {
    CHECK_NOT_NULL(vec, "Expected not null");
    CHECK_NOT_NULL(vec->internal.data, "Expected not null");

    if(vec->internal.data == 0)
        return null;
    
    return (void*)(cast(char*)vec->internal.data + (vec->internal.size - 1) * sizeof(cstlVector));
}

// Is `vec` empty?
bool vec_is_empty(cstlVector* vec) {
    CHECK_NOT_NULL(vec, "Expected not null");
    CHECK_NOT_NULL(vec->internal.data, "Expected not null");

    return vec->internal.size == 0;
}

// Returns the size of `vec` (i.e the number of bytes)
UInt64 vec_size(cstlVector* vec) {
    CHECK_NOT_NULL(vec, "Expected not null");
    CHECK_NOT_NULL(vec->internal.data, "Expected not null");

    return vec->internal.size;
}

// Returns the allocated capacity of `vec` (i.e the number of bytes)
UInt64 vec_cap(cstlVector* vec) {
    CHECK_NOT_NULL(vec, "Expected not null");
    CHECK_NOT_NULL(vec->internal.data, "Expected not null");

    return vec->internal.capacity;
}

// Clear all contents of `vec`
bool vec_clear(cstlVector* vec) {
    CHECK_NOT_NULL(vec, "Expected not null");
    CHECK_NOT_NULL(vec->internal.data, "Expected not null");

    vec->internal.size = 0;
    return true;
}

// Push an element into `vec` (at the end)
bool vec_push(cstlVector* vec, const void* data) {
    CHECK_NOT_NULL(vec, "Expected not null");
    CHECK_NOT_NULL(vec->internal.data, "Expected not null");

    if(vec->internal.size + 1 > vec->internal.capacity) {
        bool result = __vec_grow(vec, vec->internal.size + 1);
        if(!result)
            return false;
    }

    CHECK_GT(vec->internal.objsize, 0);

    if(vec->internal.data != null)
        memcpy(VECTOR_AT_MACRO(vec, vec->internal.size), data, vec->internal.objsize);

    vec->internal.size++;
    return true;
}

// Pop an element from the end of `vec`
bool vec_pop(cstlVector* vec) {
    CHECK_NOT_NULL(vec, "Expected not null");
    CHECK_NOT_NULL(vec->internal.data, "Expected not null");

    if(vec->internal.size == 0) 
        return false;
    
    vec->internal.size--;
    return true;
}

// Grow the capacity of `vec` to at least `capacity`.
// If more space is needed, grow `vec` to `capacity`, but at least by a factor of 1.5.
bool __vec_grow(cstlVector* vec, UInt64 capacity) {
    void* newdata;
    UInt64 newcapacity;

    CHECK_NOT_NULL(vec, "Expected not null");
    CHECK_NOT_NULL(vec->internal.data, "Expected not null");

    if (capacity <= vec->internal.capacity)
        return true;

    CHECK_GT(vec->internal.objsize,  0);
    CHECK_LT(capacity, (UInt64)-1/vec->internal.objsize);

    // Grow small vectors by a factor of 2, and 1.5 for larger ones
    if (vec->internal.capacity < VEC_INIT_ALLOC_CAP / vec->internal.objsize) {
        newcapacity = vec->internal.capacity + vec->internal.capacity + 1;
    } else {
        newcapacity = vec->internal.capacity + vec->internal.capacity / 2 + 1;
    }

    if (capacity > newcapacity || newcapacity >= (size_t) -1 / vec->internal.objsize)
        newcapacity = capacity;

    newdata = realloc(vec->internal.data, newcapacity * vec->internal.objsize);
    CHECK_NOT_NULL(newdata, "Expected not null");

    vec->internal.data = newdata;
    vec->internal.capacity = newcapacity;

    return true;
}