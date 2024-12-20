#pragma once

#include "./safety.h"
#include "../types/basics.h"


#define new(T) ((Result)alloc(sizeof(T)))
