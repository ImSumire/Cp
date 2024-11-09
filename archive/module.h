#pragma once

#define priv(mod, func) __private_ ## mod ## _ ## func
#define module(name, ...) typedef struct { __VA_ARGS__ } __private_##name##_mod_struct;
#define init(mod, name, ...) const __private_##mod##_mod_struct name = { __VA_ARGS__ };
