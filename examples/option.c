#define DEBUG_MODE
#include "../cp.h"


Option find(const Vector vec, const Any value) {
    i32 i = 0;

    for vec_iter(e, vec) {
        if (bin_cmp(e, value, vec.value_size))
            return Some(alloc_var_ptr(i32, i));

        i++;
    }
    return None;
}

i32 main() {
    loop {
        pass;
        break;
    }
    
    // Creating a defered vector of i32
    // defer(res_drop) Result res = vec_with_capacity(sizeof(i32), 16);
    // defer(vec_drop) Vector vec = unwrap_as(res, Vector);

    // Create an unsafe defered vector of i32 (like unwrapping it)
    defer(vec_drop) Vector vec = vec_unsafe_with_capacity(sizeof(i32), 16);
    
    // Adding some elements
    for range(i, 0, 16)
        vec_push(&vec, &i);

    // Search an valid element
    defer(opt_drop) Option result1 = find(vec, var_ptr(i32, 7));

    if (opt_is_some(result1))
        println("Index: %d", bin_cast(result1.value, i32));
    else
        println("Element not found");

    // Search an non-valid element
    defer(opt_drop) Option result2 = find(vec, var_ptr(i32, 18));

    if (opt_is_some(result2))
        println("Index: %d", bin_cast(result2.value, i32));
    else
        println("Element not found");
}
