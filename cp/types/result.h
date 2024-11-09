#pragma once

#include "./basics.h"
#include "../panic.h"
#include "../memory/packed.h"


typedef pstruct Result {
    const bool is_ok;

    union {
        untyped value;
        const char* error;
    } data;
} Result;  // `size: 16 (9 packed)` \n hi

void res_drop(Result* self) {
    if (self->is_ok) {
        free(self->data.value);
        self->data.value = nullptr;
    }
}

inline Result Ok(untyped value) {
    return (Result) { .is_ok = true, .data.value = value };
}

#ifdef ERR_WARN
    #define Err(message) _Err(__FILE__, __LINE__, message)
    
    inline Result _Err(const char* file, i32 line, const char* message) {
        _warn(file, line, message);
        return (Result) { .is_ok = false, .data.error = message };
    }
#else
    inline Result Err(const char* message) {
        return (Result) { .is_ok = false, .data.error = message };
    }
#endif
