#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../panic.h"
#include "../types/basics.h"
#include "../memory/defer.h"
#include "../memory/safety.h"
#include "../memory/packed.h"


typedef pstruct HashMap {
    Callable(hash, i32, untyped);

    i32 capacity;
    i32 count;

    i32 key_size;
    untyped keys;

    i32 value_size;
    untyped values;
} HashMap;

void hash_drop(HashMap* self) {
    free(self->values);
    self->values = nullptr;
    free(self->keys);
    self->keys = nullptr;
}

HashMap hash_new(i32 key_size, i32 value_size, i32 capacity, Callable(hash, i32, untyped)) {
    return (HashMap) {
        .hash = hash,
        .capacity = capacity,
        .count = 0,
        .key_size = key_size,
        .keys = safe_malloc(capacity * key_size),
        .value_size = value_size,
        .values = safe_malloc(capacity * value_size)
    };
}

#define hash_insert(self, key, value) _hash_insert(__FILE__, __LINE__, self, key, value)

void _hash_insert(const char* file, i32 line, HashMap* self, untyped key, untyped value) {
    if (self->count >= self->capacity) {
        _panic(file, line, "HashMap is full");
        return;
    }

    i32 index = (self->hash(key) % self->capacity + self->capacity) % self->capacity;

    // Store value
    memcpy((i8*)self->values + index * self->value_size, value, self->value_size);

    // Store key
    memcpy((i8*)self->keys + self->count * self->key_size, key, self->key_size);

    self->count++;
}

bool hash_contains_key(HashMap* self, untyped key) {
    for (i32 i = 0; i < self->count; i++) {
        if (memcmp((i8*)self->keys + i * self->key_size, key, self->key_size) == 0) {
            return true;
        }
    }
    return false;
}

untyped hash_get(HashMap* self, untyped key) {
    i32 index = (self->hash(key) % self->capacity + self->capacity) % self->capacity;

    return (i8*)self->values + index * self->value_size;
}

// Utils

i32 int_hash(untyped n) {
    return *cast(n, i32*);
}

// String hash function (djb2 algorithm)
i32 string_hash(untyped str) {
    char* s = *(char**)str;
    unsigned long hash = 5381;
    i32 c;
    while ((c = *s++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash;
}
