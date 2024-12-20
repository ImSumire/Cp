#pragma once

#include "types/basics.h"

#define __get_range(_1, _2, _3, _4, NAME, ...) NAME

#define range_1(item, end)                                                     \
    (int item = 0; item < end; item += 1)

#define range_2(item, start, end)                                              \
    (int item = start; item < end; item += 1)

#define range_3(item, start, end, step)                                        \
    (int item = start; item < end; item += step)

#define range(...)                                                             \
    __get_range(__VA_ARGS__, range_3, range_2, range_1)(__VA_ARGS__)
