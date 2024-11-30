#pragma once

#include "./types/basics.h"


#define enumerate(item, arr)                                                \
    (                                                                       \
        i32 item = 0, _size = sizeof(arr) / sizeof(arr[0]);                 \
        item < _size;                                                        \
        item++                                                              \
    )

#define range(item, start, end)                                             \
    (i32 item = start; item < end; item++)

#define each(item, array)                                                   \
    (                                                                       \
        i32 _keep = 1, _count = 0, _size = sizeof(array) / sizeof(*(array));\
        _keep && _count != _size;                                           \
        _keep = !_keep, _count++                                            \
    ) for (                                                                 \
        typeof(*array) item = *((array) + _count);                          \
        _keep;                                                              \
        _keep = !_keep                                                      \
    )

#define list_each(item, list)                                               \
    (                                                                       \
        Any _node_ptr = (&list)->head, *item;                           \
        _node_ptr != nullptr && ((item) = ((Node*)_node_ptr)->value, 1);    \
        _node_ptr = ((Node*)_node_ptr)->next                                \
    )

#define hash_keys_each(item, map)                                           \
    (                                                                       \
        i8* _ptr = (i8*)map.keys, *item = (i8*)_ptr;                        \
        _ptr < (i8*)map.keys + map.count * map.key_size;                    \
        _ptr += map.key_size, item = (i8*)_ptr                              \
    )

#define hash_values_each(item, map)                                         \
    (                                                                       \
        i32 _index = 0, _max = map.count;                                   \
        _index < _max;                                                      \
        _index++                                                            \
    ) for (                                                                 \
        Any _key = (i8*)map.keys + _index * map.key_size,               \
        *item = hash_get(&map, _key);                                       \
        _key != nullptr && item != nullptr;                                 \
        _key = nullptr                                                      \
    )

#define loop while (true)
