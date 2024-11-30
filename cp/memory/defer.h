#pragma once

/*
cleanup (cleanup_function)
The cleanup attribute runs a function when the variable goes out of scope. This attribute can only be applied to auto function scope variables; it may not be applied to parameters or variables with static storage duration. The function must take one parameter, a pointer to a type compatible with the variable. The return value of the function (if any) is ignored.
If -fexceptions is enabled, then cleanup_function will be run during the stack unwinding that happens during the processing of the exception. Note that the cleanup attribute does not allow the exception to be caught, only to perform an action. It is undefined what happens if cleanup_function does not return normally.

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Variable-Attributes.html
*/

#include <stdlib.h>
#include "../types/basics.h"


#define defer(fn) __attribute__((cleanup(fn)))

#define defered __attribute__((cleanup(_defer_cleanup)))
void _defer_cleanup(Any ptr) {
    Any* p = cast(ptr, Any*);
    if (*p) {
        free(*p);
    }
}
