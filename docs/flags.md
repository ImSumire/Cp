Here is the list of flags to modify the inner behavior of C+.

All those you see below are disabled by default, enable them using `#define ...`:
- **WARN_EXIT**: Exit the program when warn() is called
- **PANIC_CONTINUE**: Don't exit the program when panic() is called
<br>

- **DEBUG_MODE**: Displays debug messages (compatibility with the Makefile not yet done)
<br>

- **FORCE_UNPACKED**: Force packed structs to not be packed regardless to the architecture
- **FORCE_PACKED**: Force packed structs to be packed regardless to the architecture
