#pragma once

#define drop(T) _Generic((T), \
    HashMap*: hash_drop, \
    Result*: res_drop, \
    Vector*: vec_drop, \
    List*: list_drop, \
    SafeArray*: sarr_drop, \
    default: _defer_cleanup \
    )(T)

#define push(T, item) _Generic((T), \
    Vector*: vec_push, \
    List*: list_push_back \
    )(T, item)

#define test(T, ...) _Generic((T), \
    List*: list_to_str, \
    Vector*: vec_to_str \
    )(T, ##__VA_ARGS__)
