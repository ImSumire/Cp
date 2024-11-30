#pragma once

#include "./basics.h"
#include "../panic.h"
#include "../memory/packed.h"


/**
 * @typedef Result
 * @brief The `Result` struct is used to return either a successful value or an error message, 
 * allowing for error handling without exceptions.
 *
 * `size = 16 (9 packed), align = 8 (1 packed)`
 */
typedef struct packed Result {
    const bool is_ok;

    union {
        Any value;
        const char* error;
    } data;
} Result;

void res_drop(Result* self) {
    if (self->is_ok) {
        free(self->data.value);
        self->data.value = nullptr;
    }
}

#define unwrap(self) _unwrap(__FILE__, __LINE__, self)
Any _unwrap(const char* file, i32 line, Result self) {
    if (self.is_ok) {
        return self.data.value;
    }
    _panic(file, line, self.data.error);
}

#define unwrap_as(self, type) bin_cast(_unwrap(__FILE__, __LINE__, self), type)

inline static Result Ok(Any value) {
    return (Result) { .is_ok = true, .data.value = value };
}

/* inline Result OkOk() {
    return (Result) { .is_ok = true, .data.value = nullptr };
} */


static Result OkOk = { .is_ok = true, .data.value = nullptr };
// #define OkOk (Result) { .is_ok = true, .data.value = nullptr }

#ifdef ERR_WARN
    #define Err(message) _Err(__FILE__, __LINE__, message)
    
    inline static Result _Err(const char* file, i32 line, const char* message) {
        _warn(file, line, message);
        return (Result) { .is_ok = false, .data.error = message };
    }
#else
    inline static Result Err(const char* message) {
        return (Result) { .is_ok = false, .data.error = message };
    }
#endif
