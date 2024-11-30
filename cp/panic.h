#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>


#define panic(fmt, ...) _panic(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
void _panic(const char* file, i32 line, const char* fmt, ...) {
    va_list args;

    // Print the generic panic banner
    fprintf(stderr, "\x1b[37;41m PANIC \x1b[0;30m (%s:%d)\x1b[0m ", file, line);

    // Extract and print the formatted error message
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    // Print a newline for clarity
    fprintf(stderr, "\n");
    
    // If errno is set, print its value and corresponding error message
    if (errno != 0) {
        fprintf(stderr, "Error code: %d, Message: %s\n", errno, strerror(errno));
    }

    #ifdef PANIC_EXIT
        // Terminate the program
        exit(EXIT_FAILURE);
    #endif
}

#define warn(fmt, ...) _warn(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
void _warn(const char* file, i32 line, const char* fmt, ...) {
    va_list args;

    // Print the generic warn banner
    fprintf(stderr, "\x1b[37;43m WARN \x1b[0;30m (%s:%d)\x1b[0m ", file, line);

    // Extract and print the formatted error message
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    // Print a newline for clarity
    fprintf(stderr, "\n");

    #ifdef WARN_EXIT
        // Terminate the program
        exit(EXIT_FAILURE);
    #endif
}
