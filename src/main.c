#include "../cp/cp.h"


Result divide(i32 a, i32 b) {
    if (b == 0)
        return Err("Division by zero");

    i32* result = unwrap(new(i32*));
    if (!result)
        return Err("Memory allocation failed");

    *result = a / b;
    return Ok(result);
}


i32 main() {
    println("Hello, World!");

    defer(res_drop)
    Result res = divide(16, 1);

    // This block print "Divison by zero"
    if (res.is_ok)
        println("%d", *cast(res.data.value, i32*));
    else
        println("%s", res.data.error);
}
