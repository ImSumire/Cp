#pragma once

// Help: /usr/include/inttypes.h

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>  // %d


#define i8 int8_t  // `%i`
#define i16 int16_t  // `%i`
#define i32 int32_t  // `%i`
#define i64 int64_t  // `%li`

#define u8 uint8_t  // `%u`
#define u16 uint16_t  // `%u`
#define u32 uint32_t  // `%u`
#define u64 uint64_t  // `%u`

#define usize size_t  // `%zu`
#define isize ptrdiff_t  // `%td`

#define f32 float  // `%f`
#define f64 double  // `%lf`

#define Callable(name, return_type, ...) return_type (*name)(__VA_ARGS__)

#define nullptr NULL

#define untyped void*

#define cast(value, type) ((type) value)
