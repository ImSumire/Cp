#pragma once

/*
    - Single object or contiguous memory block
    - Simpler memory management
*/

#include <string.h>

#include "../types/cast.h"
#include "../types/result.h"
#include "../memory/utils.h"
#include "../memory/packed.h"
#include "../types/basics.h"


typedef struct packed Array {
    any data;

    usize size;
    usize value_size;

    usize capacity;
} Array;

void arr_drop(Array* self) {
    if (self->data != nullptr) {
        free(self->data);
        self->data = nullptr;
    }
}

Result arr_new(usize capacity, usize value_size) {
    Result arr_res = new(Array);
    if (!arr_res.is_ok)
        return Err("Memory allocation failed");

    Array* arr = arr_res.data.value;

    Result data_res = alloc(capacity * value_size);
    if (!data_res.is_ok) {
        arr_drop(arr);
        return Err("Memory allocation failed");
    }

    arr->size = 0;
    arr->capacity = capacity;
    arr->data = data_res.data.value;
    arr->value_size = value_size;

    return Ok(arr);
}

void arr_push(Array* self, any item) {
    if (self->size < self->capacity) {
        memcpy(
            (i8*)self->data + (self->size * self->value_size),
            item,
            self->value_size
        );
        self->size += 1;
    }
}

Result arr_at(Array* self, usize index) {
    if (index >= self->size)
        return Err("Index out of bounds");
    return Ok((i8*)self->data + index * self->value_size);
}
