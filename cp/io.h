#pragma once

#include <stdio.h>
#include <stdarg.h>

#include "./types/result.h"
#include "./memory/safety.h"
#include "./types/basics.h"


static inline void eprint(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, fmt, args);

    va_end(args);
}

#ifdef DEBUG_MODE
    #define debug(fmt, ...) eprint(stderr, "\x1b[37;44m DEBUG \x1b[0m " fmt "\n", ##__VA_ARGS__)
#else
    #define debug(...)
#endif

static inline void print(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    vprintf(fmt, args);

    va_end(args);
}

static inline void println(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    vprintf(fmt, args);
    print("\n");
    
    va_end(args);
}

static inline Result fmt(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    // First, we calculate the size needed to store the formatted string
    i32 size = vsnprintf(nullptr, 0, fmt, args);
    va_end(args);

    if (size < 0) {
        return Err("");  // Error occurred
    }

    // Allocate memory for the formatted string
    Result res = alloc(size + 1);
    if (!res.is_ok)
        return Err("Memory allocation failed");
    
    char* result = (char*)res.data.value;

    // Format the string and store it in the allocated buffer
    va_start(args, fmt);
    vsnprintf(result, size + 1, fmt, args);
    va_end(args);

    if (!result) {
        return Err("Formating failed");
    }

    return Ok(result);
}
