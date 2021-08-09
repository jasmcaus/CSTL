/*
  ______ ____ ________ _
 / ____/ ____|__   __/| |
| |    | (_     | |   | |      CSTL - The Coreten Standard Library
| |    \___ \   | |   | |      Languages: C, C++ and Assembly
| |___ ____) |  | |   | |____  https://github.com/jasmcaus/cstl
 \_____\_____/  |_|   \______| 

Licensed under the MIT License <http://opensource.org/licenses/MIT>
SPDX-License-Identifier: MIT
Copyright (c) 2021 Jason Dsouza <@jasmcaus>
*/

#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <coreten/io.h>

char* readFile(const char* fname) {
    FILE* file = fopen(fname, "rb"); 
    
    if(!file) {
        cstlColouredPrintf(CORETEN_COLOUR_ERROR, "Could not open file: <%s>\n", fname);
        cstlColouredPrintf(CORETEN_COLOUR_ERROR, "%s\n", !file_exists(fname) ?  
                            "FileNotFoundError: File does not exist." : "");
        exit(1);
    }

    // Get the length of the input buffer
    fseek(file, 0, SEEK_END); 
    long buff_length = ftell(file); 
    fseek(file, 0, SEEK_SET);

    char* buffer = cast(char*)malloc(sizeof(char) * (buff_length + 1) );
    if(!buffer) {
        fprintf(stderr, "Could not allocate memory for buffer for file at %s\n", fname);
		exit(1);
    }

    fread(buffer, 1, buff_length, file); 
    buffer[buff_length] = nullchar;
    fclose(file); 

    return buffer;
}

bool file_exists(const char* path) {
#ifdef WIN32
    if (GetFileAttributesA(path) != INVALID_FILE_ATTRIBUTES) return true;
#else
    // if(access(path, 0) == 0) return true;
    struct stat st;
    return !stat(path, &st);
#endif // WIN32
    return false;
}