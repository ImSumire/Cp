#include "../cp/cp.h"


i32 main() {
    usize capacity = 16;
    usize value_size = sizeof(i32);

    defer(res_drop)
    Result arr_res = arr_new(capacity, value_size);
    if (!arr_res.is_ok) {
        eprint("Array creation failed: %s\n", arr_res.data.error);
    }

    defer(arr_drop)
    Array arr = bin_cast(arr_res.data.value, Array);

    assert(arr.size == 0);
    assert(arr.capacity == capacity);
    assert(arr.value_size == value_size);

    for range(i, 20) {
        arr_push(&arr, &i);
    }

    Result fifth_res = arr_at(&arr, 4);
    assert(fifth_res.is_ok);

    Result fiftieth_res = arr_at(&arr, 49);
    assert(!fiftieth_res.is_ok);

    for (usize i = 0; i < arr.size; i++) {  // TODO: arr_iter
        assert(unwrap_as(arr_at(&arr, i), i32) == (i32)i);
    }

    println("\x1b[32;1m✓ Array test passed!");
}
