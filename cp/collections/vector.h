#pragma once

#include "../types/basics.h"
#include "../memory/defer.h"
#include "../memory/safety.h"
#include "../memory/packed.h"
#include "../loop.h"


/*
 TODO:
 - [ ] Use Safe Array instead

 // Basics
 - [ ] pop
 - [ ] append  // leaving `other` empty
 - [ ] extend

 // Resizing
 - [ ] shrink  // resize to fit the size
 - [ ] truncate  // resize to n and drop the rest
 
 // Memory
 - [ ] clone
 - [ ] clear

 // Conversions
 - [ ] slice
 - [ ] as_list
 - [ ] as_slice
 - [ ] as_sarr
 - [ ] from_list
 - [ ] from_slice
 - [ ] from_sarr
 
 // Iteration
 - [ ] retain  // map but removes all `f(x)` which returns `false`
 - [ ] Replace and move `vec_iter` to `vec_iter`
 - [ ] iter_mut
 - [ ] enumerate 
 - [ ] enumerate_mut

 // From Vector, List, Slice & SafeArray
 */


/**
 * @typedef Vector
 * @brief A dynamic array providing operations to resize, add, remove, and access elements.
 *
 * `size = 24 (20 packed), align = 8 (1 packed)`
 */
typedef struct packed Vector {
    i32 size;
    i32 capacity;
    i32 value_size;
    Any values;
} Vector;

/**
 * @def vec_iter(item, vec)
 * @brief Iterates over each item in a generic vector.
 * 
 * @param item A pointer to the current item in the vector during the iteration.
 *             The type of this pointer is `i8*` (byte pointer).
 * @param vec  The vector to iterate over.
 */
#define vec_iter(item, vec)                                                 \
    (                                                                       \
        i8* _ptr = (i8*)vec.values, *item = (i8*)_ptr;                      \
        _ptr < (i8*)vec.values + vec.size * vec.value_size;                 \
        _ptr += vec.value_size, item = (i8*)_ptr                            \
    )

/**
 * @brief Frees the allocated memory of a vector and nullifies its pointer.
 * @param self Pointer to the vector to be dropped.
 */
void vec_drop(Vector* self) {
    if (self == nullptr) {
        debug("self = nullptr");
        return;
    }

    free(self->values);
    self->values = nullptr;
}

/**
 * @brief Creates a new vector with a given value size, initialized with a capacity of 1.
 * @param value_size The size of each element in the vector.
 * @return A newly created vector.
 */
Result vec_new(i32 value_size) {
    Any values = malloc(value_size);

    if (values != nullptr) {
        Vector vec = {
            .size = 0,
            .capacity = 1,
            .value_size = value_size,
            .values = values
        };
        return Ok(&vec);
    }
    else
        return Err("Failed to allocate memory for vector");
}

Vector vec_unsafe_new(i32 value_size) {
    Any values = malloc(value_size);

    // TODO: panic

    return (Vector) {
        .size = 0,
        .capacity = 1,
        .value_size = value_size,
        .values = values
    };
}

/**
 * @brief Creates a new vector with a specified value size and initial capacity.
 * @param value_size The size of each element in the vector.
 * @param capacity Initial capacity of the vector.
 * @return A newly created vector with the specified capacity.
 */
Result vec_with_capacity(i32 value_size, i32 capacity) {
    Any values = malloc(value_size * capacity);

    if (values != nullptr) {
        Vector* vec = malloc(sizeof(Vector));

        if (vec != nullptr) {
            vec->size = 0;
            vec->capacity = capacity;
            vec->value_size = value_size;
            vec->values = values;
            return Ok(vec);
        }
        else {
            free(values);
            return Err("Failed to allocate memory for vector");
        }
    }
    else
        return Err("Failed to allocate memory for vector");
}

Vector vec_unsafe_with_capacity(i32 value_size, i32 capacity) {
    Any values = malloc(value_size * capacity);
    return (Vector) {
        .size = 0,
        .capacity = capacity,
        .value_size = value_size,
        .values = values
    };
} 

/**
 * @brief Resizes the vector's internal storage, doubling its capacity.
 * This function is called automatically when the vector exceeds its capacity.
 * @param self Pointer to the vector to resize.
 */
Result vec_resize(Vector* self) {
    self->capacity *= 2;

    Any values = realloc(self->values, self->capacity * self->value_size);

    if (values != nullptr) {
        self->values = values;
        return OkOk;
    }

    return Err("Realloc failed for vector resize");
}

/**
 * @brief Removes the element at the given index from the vector, shifting subsequent elements left.
 * @param self Pointer to the vector.
 * @param index Index of the element to remove.
 */
#define vec_remove(self, index) _vec_remove(__FILE__, __LINE__, self, index)

/**
 * @brief Internal helper function to remove an element from a vector.
 * @param file The source file name, used for debugging.
 * @param line The line number, used for debugging.
 * @param self Pointer to the vector.
 * @param index Index of the element to remove.
 */
Result _vec_remove(const char* file, i32 line, Vector* self, i32 index) {
    if (index < 0 || index > self->size) {
        // TODO: File/line debug
        // _panic(file, line, "Index out of bounds\n");
        // return;
        return Err("Index out of bounds");
    }

    // Shift elements to the left to fill the gap
    // TODO: Safety here
    memmove(
        (i8*)self->values + index * self->value_size, 
        (i8*)self->values + (index + 1) * self->value_size, 
        (self->size - index - 1) * self->value_size
    );
    
    self->size--;

    return OkOk;
}

/**
 * @brief Returns an element from the vector at the specified index.
 * This operation is O(1).
 * @param self Pointer to the vector.
 * @param index Index of the element to get.
 * @return The element at the given index.
 */
#define vec_get(self, index) _vec_get(__FILE__, __LINE__, self, index)

/**
 * @brief Internal helper function to get an element from the vector.
 * @param file The source file name, used for debugging.
 * @param line The line number, used for debugging.
 * @param self Pointer to the vector.
 * @param index Index of the element to get.
 * @return The element at the given index.
 */
Any _vec_get(const char* file, i32 line, Vector* self, i32 index) {
    if (index < 0 || index >= self->size) {
        _panic(file, line, "Index out of bounds\n");
        return nullptr;
    }

    return (i8*)self->values + index * self->value_size;
}

/**
 * @brief Adds a new element to the end of the vector, resizing it if necessary.
 * @param self Pointer to the vector.
 * @param value The element to add.
 */
Result vec_push(Vector* self, Any value) {
    if (self->size >= self->capacity) {
        Result res = vec_resize(self);
        if (!res.is_ok)
            return res;
    }

    // TODO: Safety here
    memcpy((i8*)self->values + (self->size * self->value_size), value, self->value_size);
    self->size++;

    return OkOk;
}

/**
 * @brief Inserts a new element into the vector at the specified index, shifting subsequent elements right.
 * @param self Pointer to the vector.
 * @param value The element to insert.
 * @param index The index at which to insert the element.
 */
#define vec_insert(self, value, index) _vec_insert(__FILE__, __LINE__, self, value, index)

/**
 * @brief Internal helper function to insert an element into the vector.
 * @param file The source file name, used for debugging.
 * @param line The line number, used for debugging.
 * @param self Pointer to the vector.
 * @param value The element to insert.
 * @param index The index at which to insert the element.
 */
Result _vec_insert(const char* file, i32 line, Vector* self, Any value, i32 index) {
    if (index < 0 || index > self->size) {
        // TODO: File/line debug
        // _panic(file, line, "Index out of bounds\n");
        // return;
        return Err("Index out of bounds");
    }

    if (self->size >= self->capacity) {
        Result res = vec_resize(self);
        if (!res.is_ok)
            return res;
    }

    // Shift elements to the right to make space
    // TODO: Safety here
    memmove(
        (i8*)self->values + (index + 1) * self->value_size, 
        (i8*)self->values + index * self->value_size, 
        (self->size - index) * self->value_size
    );
    
    // TODO: Safety here
    memcpy(
        (i8*)self->values + index * self->value_size,
        value,
        self->value_size
    );
    self->size++;

    return OkOk;
}

/**
 * @brief Creates a new vector by applying a transformation function to each element of the original vector.
 * @param self Pointer to the original vector.
 * @param transform A callable that takes an element and returns a transformed value.
 * @return A new vector with the transformed elements.
 */
Result vec_map(const Vector self, Callable(transform, Any, const Any)) {
    Result res = vec_with_capacity(self.value_size, self.capacity);

    if (!res.is_ok)
        return res;

    Vector vec = unwrap_as(res, Vector);
    
    for vec_iter(e, self) {
        Any transformed = transform(e);
        Result push_res = vec_push(&vec, transformed);
        free(transformed);
        if (!push_res.is_ok)
            return push_res;
        res_drop(&push_res);
    }

    res_drop(&res);
    return Ok(&vec);
}

// /**
//  * @brief Iterates through the vector, applying a function to each element.
//  * @param self Pointer to the vector.
//  * @param func A callable that takes an element and performs an operation.
//  */
// void vec_iter(const Vector* self, Callable(func, void, const Any)) {
//     for range(i, 0, self->size)
//         func((i8*)self->values + i * self->value_size);
// }

/**
 * @brief Converts the vector to a string representation using a converter function for each element.
 * @param self Pointer to the vector.
 * @param converter A callable that converts each element to a string.
 * @return A string representation of the vector.
 */
char* vec_to_str(const Vector* self, Callable(converter, char*, const Any)) {
    // TODO: Safety here
    if (self == nullptr || self->size == 0)
        return "[]";

    i32 length = 6; // "vec[]" + \0
    char* temp;
    for range(i, 0, self->size) {
        temp = converter(self->values + i * self->value_size);
        length += strlen(temp);
        free(temp);

        if (i < self->size - 1)
            length += 2; // ", "
    }

    char* result = safe_malloc(length);
    char* pos = result;

    *pos++ = 'v';
    *pos++ = 'e';
    *pos++ = 'c';
    *pos++ = '[';

    for range(i, 0, self->size) {
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

/**
 * @brief Prints the vector's string representation using a converter function for each element.
 * @param self Pointer to the vector.
 * @param converter A callable that converts each element to a string.
 */
void vec_print(const Vector* self, Callable(converter, char*, const Any)) {
    // TODO: Safety here
    char* result = vec_to_str(self, converter);
    print("%s", result);
    free(result);
}

/**
 * @brief Prints the vector's string representation with a newline at the end, 
 * using a converter function for each element.
 * @param self Pointer to the vector.
 * @param converter A callable that converts each element to a string.
 */
void vec_println(const Vector* self, Callable(converter, char*, const Any)) {
    // TODO: Safety here
    char* result = vec_to_str(self, converter);
    println("%s", result);
    free(result);
}
