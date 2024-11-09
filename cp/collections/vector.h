#pragma once


#include "../types/basics.h"
#include "../memory/defer.h"
#include "../memory/safety.h"
#include "../memory/packed.h"


typedef pstruct Vector {
    i32 size;
    i32 capacity;
    i32 value_size;
    untyped values;
} Vector;

void vec_drop(Vector* self) {
    free(self->values);
    self->values = nullptr;
}

Vector vec_new(i32 value_size) {
    return (Vector) {
        .size = 0,
        .capacity = 1,
        .value_size = value_size,
        .values = safe_malloc(value_size)
    };
}

Vector vec_with_capacity(i32 value_size, i32 capacity) {
    Vector vec;
    vec.size = 0;
    vec.capacity = capacity;
    vec.value_size = value_size;
    vec.values = safe_malloc(vec.capacity * capacity);
    return vec;
}

void vec_resize(Vector* self) {
    self->capacity *= 2;
    self->values = safe_realloc(self->values, self->capacity * self->value_size);
}

#define vec_remove(self, index) _vec_remove(__FILE__, __LINE__, self, index)

void _vec_remove(const char* file, i32 line, Vector* self, i32 index) {
    if (index < 0 || index > self->size) {
        _panic(file, line, "Index out of bounds\n");
        return;
    }

    // Shift elements to the left to fill the gap
    memmove(
        (i8*)self->values + index * self->value_size, 
        (i8*)self->values + (index + 1) * self->value_size, 
        (self->size - index - 1) * self->value_size
    );
    
    self->size--;
}

#define vec_get(self, index) _vec_get(__FILE__, __LINE__, self, index)

untyped _vec_get(const char* file, i32 line, Vector* self, i32 index) {
    if (index < 0 || index >= self->size) {
        _panic(file, line, "Index out of bounds\n");
        return nullptr;
    }

    return (i8*)self->values + index * self->value_size;
}

void vec_push(Vector* self, untyped value) {
    if (self->size >= self->capacity) {
        vec_resize(self);
    }

    memcpy((i8*)self->values + (self->size * self->value_size), value, self->value_size);
    self->size++;
}

#define vec_insert(self, value, index) _vec_insert(__FILE__, __LINE__, self, value, index)

void _vec_insert(const char* file, i32 line, Vector* self, untyped value, i32 index) {
    if (index < 0 || index > self->size) {
        _panic(file, line, "Index out of bounds\n");
        return;
    }

    if (self->size >= self->capacity) {
        vec_resize(self);
    }

    // Shift elements to the right to make space
    memmove(
        (i8*)self->values + (index + 1) * self->value_size, 
        (i8*)self->values + index * self->value_size, 
        (self->size - index) * self->value_size
    );
    
    memcpy(
        (i8*)self->values + index * self->value_size,
        value,
        self->value_size
    );
    self->size++;
}

Vector vec_map(Vector* self, Callable(transform, untyped, const untyped)) {
    Vector new_vec = vec_new(self->value_size);
    if (!self) return new_vec;

    for (i32 i = 0; i < self->size; i++) {
        untyped transformed = transform((i8*)self->values + i * self->value_size);
        vec_push(&new_vec, transformed);
        free(transformed);  // Clean up the transformed value after copying
    }
    return new_vec;
}

void vec_iter(const Vector* self, Callable(func, void, const untyped)) {
    for (i32 i = 0; i < self->size; i++) {
        func((i8*)self->values + i * self->value_size);
    }
}

char* vec_to_str(const Vector* self, Callable(converter, char*, const untyped)) {
    if (self == nullptr || self->size == 0)
        return "[]";

    i32 length = 6; // "vec[]" + \0
    char* temp;
    for (i32 i = 0; i < self->size; i++) {
        temp = converter(self->values + i * self->value_size);
        length += strlen(temp);
        free(temp);

        if (i < self->size - 1) {
            length += 2; // ", "
        }
    }

    char* result = safe_malloc(length);
    char* pos = result;

    *pos++ = 'v';
    *pos++ = 'e';
    *pos++ = 'c';
    *pos++ = '[';

    for (i32 i = 0; i < self->size; i++) {
        temp = converter(self->values + i * self->value_size);
        i32 len = strlen(temp);
        memcpy(pos, temp, len);
        pos += len;
        free(temp);

        if (i < self->size - 1) {
            *pos++ = ',';
            *pos++ = ' ';
        }
    }
    *pos++ = ']';
    *pos = '\0';

    return result;
}

void vec_print(const Vector* self, Callable(converter, char*, const untyped)) {
    char* result = vec_to_str(self, converter);
    print("%s", result);
    free(result);
}

void vec_println(const Vector* self, Callable(converter, char*, const untyped)) {
    char* result = vec_to_str(self, converter);
    println("%s", result);
    free(result);
}
