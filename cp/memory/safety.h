#pragma once

#include <stdlib.h>

#include "../keywords.h"
#include "../types/result.h"
#include "../types/basics.h"


#define alloc(size) _safe_malloc(__FILE__, __LINE__, size)

// nodiscard
Result _safe_malloc(const char* file, i32 line, usize size) {
    any ptr = malloc(size);

    if (!ptr)
        return Err("Memory allocation failed");

    return Ok(ptr);
}
