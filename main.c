// #define FORCE_PACKED
// #define FORCE_UNPACKED
// #define PANIC_EXIT
// #define WARN_EXIT
// #define ERR_WARN
#define DEBUG_MODE
#include "cp.h"

i32 comp_i32(const Any a, const Any b) {
    i32 ia = bin_cast(a, i32);
    i32 ib = bin_cast(b, i32);
    return (ia > ib) - (ia < ib);
}

char* i32_to_str(const Any value) {
    return fmt("%i", bin_cast(value, i32));
}

void print_i32(const Any value) {
    print("%i", bin_cast(value, i32));
}

Any double_i32(const Any value) {
    i32* new_value = safe_malloc(sizeof(i32));
    *new_value = bin_cast(value, i32) * 2;
    return new_value;
}

Result divide(const i32 a, const i32 b) {
    if (b == 0)
        return Err("Division by zero");

    i32* result = malloc(sizeof(i32));
    if (!result)
        return Err("Memory allocation failed");

    *result = a / b;
    return Ok(result);
}

void banner(char* content) {
    println("\n\x1b[30;47;1m %s \x1b[0m\n", content);
}

i32 main() {
    /*
         ___                 _  _   
        | _ \ ___  ___ _  _ | || |_ 
        |   // -_)(_-<| || || ||  _|
        |_|_\\___|/__/ \_,_||_| \__|
     */
    banner("Result");

    defer(res_drop) Result res1 = divide(16, 3);
    if (res1.is_ok)
        println("16 / 3: %i", bin_cast(res1.data.value, i32));
    else
        println("16 / 3: %s", res1.data.error);

    defer(res_drop) Result res2 = divide(42, 0);
    if (res2.is_ok)
        println("42 / 0: %i", bin_cast(res2.data.value, i32));
    else
        println("42 / 0: %s", res2.data.error);


    /*
         _     _      _   
        | |   (_) ___| |_ 
        | |__ | |(_-<|  _|
        |____||_|/__/ \__|
     */
    banner("List");

    defer(list_drop) List list = list_new(sizeof(i32));
    for range(i, 0, 10)
        list_push_back(&list, &i);
    println("0 to 9 push:");
    for list_each(e, list)
        print("%i, ", bin_cast(e, i32));
    println("");

    for range(i, 0, 10)
        list_push(&list, &i);
    println("\n0 to 9 push (front):");
    for list_each(e, list)
        print("%i, ", bin_cast(e, i32));
    println("");

    println("\nRemove at 0 and insert 123 at 0");
    list_remove(&list, 0);
    list_insert(&list, var_ptr(i32, 123), 0);
    
    print("\nBuilt-in list_println: ");
    list_println(&list, i32_to_str);

    println("\n5th element: %i", bin_cast(list_get(&list, 4), i32));

    defer(list_drop) List list2 = list_map(&list, double_i32);
    print("\nMapped list: ");
    for list_each(e, list2)
        print("%i, ", bin_cast(e, i32));
    println("");

    /* 
        __   __         _             
        \ \ / /___  __ | |_  ___  _ _ 
         \ V // -_)/ _||  _|/ _ \| '_|
          \_/ \___|\__| \__|\___/|_|  
     */
    banner("Vector");

    defer(res_drop) Result res = vec_new(sizeof(i32));
    defer(vec_drop) Vector vec = unwrap_as(res, Vector);

    for range(i, 0, 10)
        vec_push(&vec, &i);
    println("0 to 9 push:");
    for vec_iter(e, vec)
        print("%i, ", bin_cast(e, i32));
    println("");

    println("\nRemove at 0 and insert 123 at 0");
    vec_remove(&vec, 0);
    vec_insert(&vec, var_ptr(i32, 123), 0);

    println("\nBuilt-in vec_println:");
    vec_println(&vec, i32_to_str);

    defer(res_drop) Result res3 = vec_map(vec, double_i32);
    defer(vec_drop) Vector vec2 = unwrap_as(res3, Vector);

    println("\nMapped vector:");
    for vec_iter(e, vec2)
        print("%i, ", bin_cast(e, i32));
    println("");

    println("\nWith default capacity vector:");
    defer(res_drop) Result res4 = vec_with_capacity(sizeof(i32), 64);
    defer(vec_drop) Vector vec3 = unwrap_as(res4, Vector);

    println("- Capacity (before): %i", vec3.capacity);  // 64

    for range(i, 0, 64)
        vec_push(&vec3, &i);
    println("- Capacity (after): %i", vec3.capacity);  // 64 (no resizing)

    /*     _                         
          /_\   _ _  _ _  __ _  _  _ 
         / _ \ | '_|| '_|/ _` || || |
        /_/ \_\|_|  |_|  \__,_| \_, |
                                |__/ 
    */
    /* banner("Vanill Arrays");
    i32 numbers[] = { 8, 6, 3, 7, 0, 2, 1, 5, 9 };

    print("Before sorting: [");
    for each(e, numbers)
        print("%i, ", e);
    println("]");

    qsort(numbers, comp_i32);

    print("After sorting: [");
    for each(e, numbers)
        print("%i, ", e);
    println("]"); */

    /*   ___                        _    _    _             
        | __|___  _ _  _ __   __ _ | |_ | |_ (_) _ _   __ _ 
        | _|/ _ \| '_|| '  \ / _` ||  _||  _|| || ' \ / _` |
        |_| \___/|_|  |_|_|_|\__,_| \__| \__||_||_||_|\__, |
                                                      |___/ 
     */
    banner("Formatting");

    println("\x1b[34mfmt\x1b[33m(\x1b[32m\"Hello, %%s! Your score is %%i.\"\x1b[30m, \x1b[32m\"Alice\"\x1b[30m, \x1b[31m42\x1b[33m)\x1b[30m;\x1b[0m");
    defered char* str = fmt("Hello, %s! Your score is %i.", "Alice", 42);
    println("%s", str);

    /*   _                        
        | |    ___  ___  _ __  ___
        | |__ / _ \/ _ \| '_ \(_-<
        |____|\___/\___/| .__//__/
                        |_|       
     */
    banner("Loops");

    println("Range 0 to 15:");
    for range(i, 0, 16)
        print("%i, ", i);
    println("");

    loop {  // Infinite loop
        pass;  // Useless but I don't care
        break;
    }

    /*   ___        _                       _             
        |   \  ___ | |__  _  _  __ _  __ _ (_) _ _   __ _ 
        | |) |/ -_)| '_ \| || |/ _` |/ _` || || ' \ / _` |
        |___/ \___||_.__/ \_,_|\__, |\__, ||_||_||_|\__, |
                               |___/ |___/          |___/ 
     */
    banner("Debugging");

    println("Only displayed if flag \x1b[33mDEBUG_MODE\x1b[0m is defined");
    debug("Hi!");

    /*   ___         __            _             
        |   \  ___  / _| ___  _ _ (_) _ _   __ _ 
        | |) |/ -_)|  _|/ -_)| '_|| || ' \ / _` |
        |___/ \___||_|  \___||_|  |_||_||_|\__, |
                                           |___/ 
     */
    banner("Defering");

    defer(vec_drop) Vector vec4 = vec_unsafe_new(sizeof(i32));
    println("Nothing very interesting to display except that anything “defered” will be dropped as soon as it's out of scope.");
    println("\x1b[31mDo not use it in a function return value, as it will be dropped on return!\x1b[0m");

    /*
         _  _            _     __  __             
        | || | __ _  ___| |_  |  \/  | __ _  _ __ 
        | __ |/ _` |(_-<| ' \ | |\/| |/ _` || '_ \
        |_||_|\__,_|/__/|_||_||_|  |_|\__,_|| .__/
                                            |_|   
    */
    banner("HashMap");

    defer(hash_drop) HashMap hash_map = hash_new(sizeof(i32), sizeof(i32), 8, int_hash);
    
    for range(i, 0, 8)
        hash_insert(&hash_map, &i, var_ptr(i32, i * 7));

    println("All keys:");
    for hash_keys_each(k, hash_map)
        print("%i, ", bin_cast(k, i32));
    println("");

    println("\nAll values pairs:");
    for hash_values_each(v, hash_map)
        print("%i, ", bin_cast(v, i32));
    println("");

    println("\nAll keys/values pairs:");
    for hash_keys_each(k, hash_map)
        println("%i → %i", bin_cast(k, i32), bin_cast(hash_get(&hash_map, k), i32));
}
