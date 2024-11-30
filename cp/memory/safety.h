#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../panic.h"
#include "../types/basics.h"


#define safe_malloc(size) _safe_malloc(__FILE__, __LINE__, size)
Any _safe_malloc(const char* file, i32 line, size_t size) {
    Any ptr = malloc(size);
    if (!ptr) {
        _panic(file, line, "Memory allocation failed");
        return nullptr;
    }
    return ptr;
}

#define safe_realloc(ptr, size) _safe_realloc(__FILE__, __LINE__, ptr, size)
Any _safe_realloc(const char* file, i32 line, Any _ptr, size_t size) {
    Any ptr = realloc(_ptr, size);
    if (!ptr) {
        _panic(file, line, "Memory reallocation failed");
        return nullptr;
    }
    return ptr;    
}
