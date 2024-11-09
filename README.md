<div align="center">
    <pre>
  __|  |  
 (  __ __|
\___| _|  
‿୨♡୧‿
A modern, safer approach to C
  </pre>

  [![License: GNU](https://img.shields.io/badge/License-GNU-7245a8?style=for-the-badge)](https://www.gnu.org/)
  [![Gcc: 13](https://img.shields.io/badge/Gcc-13-3d51a1?style=for-the-badge)](https://gcc.gnu.org/)

</div>

**C+** is a modern C library designed to enhance the C language with safety, convenience, and expressiveness. By introducing advanced utilities like error handling, smart memory management, data structures, and macros for loops and type safety, C+ brings C development closer to the standards of modern systems languages like [Rust](https://www.rust-lang.org/) and [Zig](https://ziglang.org/), all while staying true to C’s lightweight, performance-oriented core.

## Features
- **Result Types**: Structured error handling with `Result` types, inspired by [Rust](https://www.rust-lang.org/), eliminates the need for error codes and null pointers.
- **Panic System**: Safe, optional error handling with customizable `panic`/`warn` behavior.
- **Defer Mechanism**: Automatic resource cleanup at the end of scope with a [Zig](https://ziglang.org/)-like mechanism.
- **Smart Data Structures**: Packed structures, `Option` type, byte precision types and a collection of data structures (e.g. `HashMap`, `List`, `Vector`).
- **Loop Utilities**: Macros for range, enumerate, each, and custom data structure iteration.
- **Custom Allocators**: Define custom memory allocators (e.g., `Arena`, `Pool`) for more flexible and performant memory management.
- **Debug Helpers**: Optional debug macros and stack tracing for easier debugging.

## Usage
### 1. Basic Example - Result Type and Error Handling
```c
// Basic error-safe function using `Result`
Result divide(i32 a, i32 b) {
    if (b == 0)
        return Err("Division by zero");

    i32* result = malloc(sizeof(i32));
    if (!result)
        return Err("Memory allocation failed");

    *result = a / b;
    return Ok(result);
}

int main() {
    defer(res_drop) Result r = divide(16, 0);

    // This block print "Divison by zero"
    if (r.is_ok)
        println("%d", *cast(r.data.value, i32*));
    else
        println("%s", r.data.error);
}
```

### 2. Memory Management with Defer
```c
// Will be freed when the variable goes out of scope
defered int *data = malloc(sizeof(int) * 10);
```

### 3. Custom Loop Macros
```c
defer(list_drop) List list = list_new(sizeof(i32));

// Add some elements
for range(i, 0, 10)
    list_push_back(&list, &i);

// Print the list element
for list_each(e, list)
    print("%d, ", *cast(e, i32*));
println("");
```

## Documentation
*The documentation is currently being written*

## Future of C+
- Try to add Ownership and Borrowing like Rust to improve code quality and safety
- Improve source code to make it clear and better vsc compatibility
- Document every type and function (and online doc with Github Pages)
- Add more data structures (e.g. Set, String, Queue)

## Inspiration
- [klib](https://github.com/attractivechaos/klib)
- [Cello](https://libcello.org/)
- [stb](https://github.com/nothings/stb)

## Contributing
**Contributions are welcome!** Please fork this repository and submit a pull request. For major changes, open an issue to discuss your proposal first.
