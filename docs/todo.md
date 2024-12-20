# Docs
- [ ] C+ Style/Convention
    - pragma
    - PascalCase/camelCase (https://hackmd.io/@Octal9139/BkCOF_7IA)
    - defering
- [ ] Env advices (Inlay, ...)

# Keywords
- [x] defer (__attribute__((cleanup(fn))))
- [x] packed (__attribute__((__packed__)))
- [x] unreachable (__builtin_unreachable())
- [x] assert
- [x] static_assert
- [x] deprecated (__attribute__ ((deprecated)))
- [ ] nodiscard

# Safety
- [ ] Result (50%)
    - res_to_opt
    - expect (panics if is an Err)
    - expect_err (... Ok)
    - unwrap_err
    - map
    - map_or
- [ ] Option

# Generic Shortcuts
- [ ] drop
- [ ] push
- [ ] pop
- [ ] at

# Collection
- [x] Array
- [ ] PointerArray
- [ ] Vector
- [ ] PointerVector
- [ ] Stack
- [ ] String

- [ ] List
- [ ] Queue
- [ ] Priority Queue

- [ ] HashMap
- [ ] HashSet

- [ ] BTree

- [ ] Complex

# Types
- [ ] CString (char*)
- [ ] File
- [ ] Mutex (lock/unlock)
- [ ] Thread-Safe Collections

# Makefile
- [x] Force build when no target (in case when gcc didn't compile)
- [x] Run tests from `tests/`

# Maybe
- [ ] Package Manager
- [ ] Garbage Collector (with mark(ptr, fn), copyable, ...)
