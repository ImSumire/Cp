#pragma once

#include "./basics.h"

/**
 * @typedef Option
 * @brief Used to return an optional value or None, allowing for error
 * handling without exceptions.
 *
 * `size = 8, align = 8 (1 packed)`
*/
typedef struct Option {
    Any value;
} Option;

static inline bool opt_is_some(Option opt) {
    return opt.value != nullptr;
}

static inline bool opt_is_none(Option opt) {
    return opt.value == nullptr;
}

void opt_drop(Option* self) {
    if (opt_is_some(*self)) {
        free(self->value);
        self->value = nullptr;
    }
}

inline static Option Some(Any value) {
    return (Option) { .value = value };
}

#define None (Option) { .value = nullptr }

#define pass {}
