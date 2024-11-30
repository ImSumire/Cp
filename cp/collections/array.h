#pragma once

#include <stdlib.h>

#include "../types/basics.h"
#include "../memory/safety.h"


typedef struct SafeArray {
    Any values;
    usize size;
} SafeArray;

SafeArray sarr_new(usize size, i32 value_size) {
    return (SafeArray) {
        .size = size,
        .values = safe_malloc(size * value_size)
    };
}

void sarr_drop(SafeArray* self) {
    free(self->values);
    self->values = nullptr;
}

// TODO: Safe get, set, ...
