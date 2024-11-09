// #define FORCE_PACKED
// #define FORCE_UNPACKED
// #define PANIC_EXIT
// #define WARN_EXIT
// #define ERR_WARN
#define DEBUG_MODE
#include "cp.h"

i32 comp_i32(const untyped a, const untyped b) {
    i32 arg1 = *cast(a, const i32*);
    i32 arg2 = *cast(b, const i32*);
    return (arg1 > arg2) - (arg1 < arg2);
}

char* i32_to_str(const untyped value) {
    return fmt("%d", *cast(value, const i32*));
}

void print_i32(const untyped value) {
    print("%d, ", *cast(value, const i32*));
}

untyped double_i32(const untyped value) {
    i32* new_value = safe_malloc(sizeof(i32));
    *new_value = *cast(value, const i32*) * 2;
    return new_value;
}

Result divide(i32 a, i32 b) {
    if (b == 0)
        return Err("Division by zero");

    i32* result = malloc(sizeof(i32));
    if (!result) {
        return Err("Memory allocation failed");
    }
    *result = a / b;
    return Ok(result);
}

i32 main() {
    /* Sizes */
    println("Sizes: ");
    println("Option: %d", 0);
    println("List: %d", sizeof(List));
    println("Node: %d", sizeof(Node));
    println("Result: %d", sizeof(Result));
    println("Vector: %d", sizeof(Vector));
    println("HashMap: %d", sizeof(HashMap));
    println("SafeArray: %d", sizeof(SafeArray));

    /* Result */
    println("\nResult: ");
    defer(res_drop) Result r1 = divide(16, 3);
    if (r1.is_ok) {
        println("%d", *cast(r1.data.value, i32*));
    }
    else {
        println("%s", r1.data.error);
    }

    defer(res_drop) Result r2 = divide(16, 0);
    if (r2.is_ok) {
        println("%d", *cast(r2.data.value, i32*));
    }
    else {
        println("%s", r2.data.error);
    }

    // Vector test = vec_new(sizeof(i32));
    // i32 crashptdr = cast(vec_get(&test, 0), i32);

    /* List */
    println("\nList: ");
    defer(list_drop) List list = list_new(sizeof(i32));
    for range(i, 0, 10)
        list_push_back(&list, &i);

    for range(i, 0, 10)
        list_push_back(&list, &i);

    for list_each(e, list) {
        print("%d, ", *cast(e, i32*));
    }
    println("");

    list_iter(&list, print_i32);
    println("");

    list_remove(&list, 0);

    i32 n = 123;
    list_insert(&list, &n, 0);

    list_println(&list, i32_to_str);

    // i32 ml = cast(list_get(&list, 0), i32);

    defer(list_drop) List list2 = list_map(&list, double_i32);

    /* Vector */
    println("\nVector: ");
    defer(vec_drop) Vector vec = vec_new(sizeof(i32));
    for range(i, 0, 10) {
        vec_push(&vec, &i);
    }

    for vec_each(e, vec) {
        print("%d, ", *cast(e, i32*));
    }
    println("");

    vec_iter(&vec, print_i32);
    println("");

    vec_remove(&vec, 0);
    vec_insert(&vec, &n, 0);

    vec_println(&vec, i32_to_str);

    // i32 mv = cast(vec_get(&vec, 0), i32);

    defer(vec_drop) Vector vec2 = vec_map(&vec, double_i32);

    defer(vec_drop) Vector vec3 = vec_with_capacity(sizeof(i32), 128);
    for range(i, 0, 64)
        vec_push(&vec3, &i);

    /* Array */
    println("\nVanilla Arrays: ");
    i32 numbers[] = { 8, 6, 3, 7, 0, 2, 1, 5, 9 };

    print("Before sorting: [");
    for each(e, numbers) {
        print("%d", e);
        if (e != numbers[sizeof(numbers) / sizeof(*(numbers)) - 1]) {
            print(", ");
        }
    }
    println("]");

    qsort(numbers, comp_i32);

    print("After sorting: [");
    for each(e, numbers) {
        print("%d", e);
        if (e != numbers[sizeof(numbers) / sizeof(*(numbers)) - 1]) {
            print(", ");
        }
    }
    println("]");

    /* Formatting */
    println("\nFormatting: ");
    defered char* str = fmt("Hello, %s! Your score is %d.", "Alice", 42);
    print("%s\n", str);

    /* Range */
    println("\nRange: ");
    for range(i, 0, 16) {
        print("%d, ", i);
    }
    println("");

    /* Debugging */
    println("\nDebugging: ");
    debug("Hi!");

    /* Defering */
    // vec NEED to be initialized
    defer(vec_drop) Vector vec4 = vec_new(sizeof(i32));

    /* HashMap */
    println("\nHashMap: ");
    defer(hash_drop) HashMap hash_map = hash_new(sizeof(i32), sizeof(i32), 8, int_hash);
    
    for range(i, 0, 8) {
        i32 value = i * 7;
        hash_insert(&hash_map, &i, &value);
    }
    
    /* for (i32 i = 0; i < hash_map.count; i++) {
        i32 key = *cast(hash_map.keys + i * hash_map.key_size, i8*);
        i32 value = *cast(hash_get(&hash_map, &key), i32*);
        println("%d → %d", key, value);
    }
    println(""); */

    for hash_keys_each(k, hash_map) {
        print("%d, ", *cast(k, i32*));
    }
    println("");

    for hash_values_each(v, hash_map) {
        print("%d, ", *cast(v, i32*));
    }
    println("");
}
