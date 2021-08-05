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

#ifndef CSTL_IO_H
#define CSTL_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <cstl/types.h>
#include <cstl/debug.h>

typedef struct File {
    char* full_path;
    char* basename;
    int fileid;

    char* contents;
} File;

char* readFile(const char* fname);
bool file_exists(char* path);

char* readFile(const char* fname) {
    FILE* file = fopen(fname, "rb"); 
    
    if(!file) {
        cstlColouredPrintf(CSTL_COLOUR_ERROR, "Could not open file: <%s>\n", fname);
        cstlColouredPrintf(CSTL_COLOUR_ERROR, "%s\n", !file_exists(fname) ?  
                            "FileNotFoundError: File does not exist." : "");
        exit(1);
    }

    // Get the length of the input buffer
    fseek(file, 0, SEEK_END); 
    long buff_length = ftell(file); 
    fseek(file, 0, SEEK_SET);

    char* buffer = cast(char*)malloc(sizeof(char) * (buff_length + 1) );
    if(!buffer) {
        printf("Could not allocate memory for buffer for file at %s\n", fname);
		exit(1);
    }

    fread(buffer, 1, buff_length, file); 
    buffer[buff_length] = nullchar;
    fclose(file); 

    return buffer;
}


bool file_exists(char* path) {
    struct stat st;
    return !stat(path, &st);
}

#endif // CSTL_IO_H