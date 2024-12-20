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

#### Cons
- **Reduced Control**: Higher-level abstractions can obscure low-level details, limiting fine-grained control over performance-critical operations.
- **Compiler Optimization Challenges**: Frequent use of casting (with `void*`) can hinder the compiler's ability to perform optimizations.
- **Lack of Type Safety**: `void*` usage removes type information, increasing the risk of runtime errors and requiring manual type management.
- **Potential for Subtle Bugs**: Absence of compile-time type checking makes it easier for type mismatches to go unnoticed, leading to hard-to-debug runtime issues.
- **Missed Optimization Opportunities**: Without type-specific information, the compiler cannot apply advanced optimizations like loop unrolling or vectorization, which can degrade performance.

#### Pros
- **Faster Development**: Streamlined workflows and abstraction layers facilitate rapid development and reduce boilerplate code.
- **Simplified Memory Management**: Features like deferring and garbage collection (currently in progress) simplify handling of memory, reducing the risk of memory leaks or dangling pointers.
- **Improved Code Quality**: Clear syntax and structured conventions enhance readability and maintainability of the codebase.
- **Developer-Friendly Tooling**: An intuitive, [Cargo](https://doc.rust-lang.org/cargo/)-like environment improves build, checks, and tests efficiency.

#### Production
C+ is a funny, serious, and innovative library that showcases what can be done to make C programming more modern and enjoyable. However, for production-level software, it’s generally wiser to rely on established languages like **C**, **C++**, or **Rust**, or others that are tailored for robustness, performance, and long-term maintainability.

Use C+ as an experimental tool, a teaching resource, or even as a source of inspiration. But for mission-critical systems, stick with languages and tools that have stood the test of time. C+ may not be the best hammer for every nail — but it’s certainly a cool one to have in your toolbox hehe!

## Usage
#### Error Handling using Result
```c
// Basic error-safe function using `Result`
Result divide(i32 a, i32 b) {
    if (b == 0)
        return Err("Division by zero");

    i32* result = unwrap(new(i32*));
    if (!result)
        return Err("Memory allocation failed");

    *result = a / b;
    return Ok(result);
}

int main() {
    defer(res_drop)
    Result res = divide(16, 1);

    // This block print "Divison by zero"
    if (res.is_ok)
        println("%d", *cast(res.data.value, i32*));
    else
        println("%s", res.data.error);
}
```

#### Memory Management with Defering
```c
// Will be freed when the variable goes out of scope
defered int* data = unwrap(alloc(sizeof(int) * 12));
```

#### Custom Iterators Macros
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
- [Zig](https://ziglang.org/) Memory management
- [Rust](https://www.rust-lang.org/) Memory safety and error handling
- [klib](https://github.com/attractivechaos/klib) Global inspiration
- [Cello](https://libcello.org/) Abusive usage of void*
- [stb](https://github.com/nothings/stb) Standalone support (I'm waiting for a stable version to do it)

## Contributing
**Contributions are welcome!** Please fork this repository and submit a pull request. For major changes, open an issue to discuss your proposal first.
