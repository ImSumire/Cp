#include "../cp.h"


i32 main() {
    println("List: size = %d, align = %d", sizeof(List), _Alignof(List));
    println("Node: size = %d, align = %d", sizeof(Node), _Alignof(Node));
    println("Option: size = %d, align = %d", sizeof(Option), _Alignof(Option));
    println("Result: size = %d, align = %d", sizeof(Result), _Alignof(Result));
    println("Vector: size = %d, align = %d", sizeof(Vector), _Alignof(Vector));
    println("HashMap: size = %d, align = %d", sizeof(HashMap), _Alignof(HashMap));
    println("SafeArray: size = %d, align = %d", sizeof(SafeArray), _Alignof(SafeArray));
    println("Any: size = %d, align = %d", sizeof(Any), _Alignof(Any));
}
