#include "../cp.h"


Result foo() {
    return OkOk;
}

Result bar() {
    return Ok(nullptr);
}

Result zoo() {
    i32 i = 0;
    return Ok(&i);
}

i32 main() {
    Result a = foo();
    Result b = bar();
    Result c = zoo();
}
