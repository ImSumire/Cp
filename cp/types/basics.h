#pragma once

// Help: /usr/include/inttypes.h

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>  // %d


/**
 * @typedef i8
 * @brief A shorthand for an 8-bit signed integer.
 * 
 * `size = 1`
 * 
 * Format specifier: `%i`
*/
typedef int8_t i8;

/**
 * @typedef i16
 * @brief A shorthand for a 16-bit signed integer.
 * 
 * Size: 16 bits (2 bytes).
 * 
 * Format specifier: `%i`
 */
typedef int16_t i16;

/**
 * @typedef i32
 * @brief A shorthand for a 32-bit signed integer.
 * 
 * Size: 32 bits (4 bytes).
 * 
 * Format specifier: `%i`
 */
typedef int32_t i32;

/**
 * @typedef i64
 * @brief A shorthand for a 64-bit signed integer.
 * 
 * Size: 64 bits (8 bytes).
 * 
 * Format specifier: `%li`
 */
typedef int64_t i64;

/**
 * @typedef u8
 * @brief A shorthand for an 8-bit unsigned integer.
 * 
 * Size: 8 bits (1 byte).
 * 
 * Format specifier: `%u`
 */
typedef uint8_t u8;

/**
 * @typedef u16
 * @brief A shorthand for a 16-bit unsigned integer.
 * 
 * Size: 16 bits (2 bytes).
 * 
 * Format specifier: `%u`
 */
typedef uint16_t u16;

/**
 * @typedef u32
 * @brief A shorthand for a 32-bit unsigned integer.
 * 
 * Size: 32 bits (4 bytes).
 * 
 * Format specifier: `%u`
 */
typedef uint32_t u32;

/**
 * @typedef u64
 * @brief A shorthand for a 64-bit unsigned integer.
 * 
 * Size: 64 bits (8 bytes).
 * 
 * Format specifier: `%u`
 */
typedef uint64_t u64;

/**
 * @typedef usize
 * @brief A shorthand for the `size_t` type, representing the size of an object.
 * 
 * Format specifier: `%zu`
 */
typedef size_t usize;

/**
 * @typedef isize
 * @brief A shorthand for the `ptrdiff_t` type, representing the difference between two pointers.
 * 
 * Format specifier: `%td`
 */
typedef ptrdiff_t isize;

/**
 * @typedef f32
 * @brief A shorthand for the 32-bit floating-point type.
 * 
 * Format specifier: `%f`
 */
typedef float f32;

/**
 * @typedef f64
 * @brief A shorthand for the 64-bit floating-point type (double precision).
 * 
 * Format specifier: `%lf`
 */
typedef double f64;

/**
 * @def Fn(name, return_type, ...)
 * @brief Defines a callable function pointer.
 * 
 * @param name The name of the function pointer.
 * @param return_type The return type of the function.
 * @param ... The parameter types for the function.
 * 
 * ---
 */
#define Fn(name, return_type, ...) return_type (*name)(__VA_ARGS__)

/**
 * @def nullptr
 * @brief Defines a shorthand for the `NULL` pointer.
 * 
 * ---
 */
#define nullptr NULL

/**
 * @typedef any
 * @brief A shorthand for the `void*` type, representing an untyped pointer.
 */
typedef void* any;
