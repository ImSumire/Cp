#include "cp.h"


i32 main() {
    defer(vec_drop) Vector vec = vec_with_capacity(sizeof(i32), 32);

    for range(i, 0, 32)
        vec_push(&vec, &i);
    
    for vec_iter(i, vec)
        print("%d ", *cast(i, i32*));
    println("");
}
