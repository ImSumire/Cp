#pragma once


#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "./panic.h"
#include "./types/basics.h"


#ifdef DEBUG_MODE
    #define debug(fmt, ...) fprintf(stderr, "\x1b[37;44m DEBUG \x1b[0m " fmt "\n", ##__VA_ARGS__)
#else
    #define debug(...)
#endif

static inline void print(const char* __format, ...) {
    va_list args;
    va_start(args, __format);

    vprintf(__format, args);

    va_end(args);
}

static inline void println(const char* __format, ...) {
    va_list args;
    va_start(args, __format);

    vprintf(__format, args); // Print the formatted string
    print("\n"); // Print a newline
    
    va_end(args);
}

#define fmt(fmt, ...) _fmt(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
static inline char* _fmt(const char* file, i32 line, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    // First, we calculate the size needed to store the formatted string
    i32 size = vsnprintf(nullptr, 0, fmt, args);
    va_end(args);

    if (size < 0) {
        return nullptr;  // Error occurred
    }

    // Allocate memory for the formatted string
    char* result = malloc(size + 1);
    if (!result) {
        return nullptr;  // Memory allocation failed
    }

    // Format the string and store it in the allocated buffer
    va_start(args, fmt);
    vsnprintf(result, size + 1, fmt, args);
    va_end(args);

    if (!result) {
        _panic(file, line, "Formating failed\n");
        return nullptr;
    }

    return result;
}
