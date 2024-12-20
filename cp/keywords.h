#pragma once

#define unreachable __builtin_unreachable()

#define deprecated __attribute__((deprecated))

#define static_assert _Static_assert

#define nodiscard __attribute__((warn_unused_result, error("\x1b[1;4;31mIgnoring return value is not allowed\x1b[0m")))
