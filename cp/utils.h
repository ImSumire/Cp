#pragma once

#include <string.h>

#include "types/basics.h"

bool bin_cmp(Any a, Any b, usize size) {
    return memcmp(a, b, size) == 0;
}
