#pragma once

#include <stdlib.h>


#define qsort(arr, comp) qsort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), comp)

// TODO: Vector, List and SafeArray sorting
