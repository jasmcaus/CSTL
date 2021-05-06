/*
  ______ ____ ________ _
 / ____/ ____|__   __/| |
| |    | (_     | |   | |      CSTL - The neatest rewrite of the C/C++ Standard Library
| |    \___ \   | |   | |      Language: C
| |___ ____) |  | |   | |____  https://github.com/jasmcaus/CSTL
 \_____\_____/  |_|   \______| 

Licensed under the MIT License <http://opensource.org/licenses/MIT>
SPDX-License-Identifier: MIT
Copyright (c) 2021 Jason Dsouza <http://github.com/jasmcaus>
*/

#ifndef _CSTL_IO_H
#define _CSTL_IO_H

#ifdef __cplusplus

#include <fstream>
#include <sstream>
#include <string> 
#include <iostream>

namespace cstl {

// Read file contents
// std::string read_File(const std::string& fname) {
//     std::ifstream stream(fname); 
// 	std::string buffer; 

//     if(!stream) {
//         std::cout << "Coud not open file: " << fname << "\n";
//         std::abort();
//     }

//     std::ostringstream ss;
//     ss << stream.rdbuf();
//     buffer = ss.str();
//     stream.close();

//     return buffer;
// }

int hello_world(const int x) {
    std::cout << x ;
}

} // namespace cstl

#else 

#include <stdio.h>

// C-version
char* readFile(const char* fname) {
    FILE* file = fopen(fname, "rb"); 
    
    if(!file) { 
        printf("Could not open file: <%s>\n", fname);
        // std::abort(2);
    }

    // Get the length of the input buffer
    fseek(file, 0, SEEK_END); 
    long buf_length = ftell(file); 
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(sizeof(char) * (buf_length + 1) );
    if(!buffer) {
        printf("Could not allocate memory for buffer for file at %s\n", fname);
		exit(1);
    }

    fread(buffer, 1, buf_length, file); 
    buffer[buf_length] = nullchar; // null char 
    fclose(file); 

    return buffer;
}

#endif // __cplusplus 

#endif // _CSTL_IO_H