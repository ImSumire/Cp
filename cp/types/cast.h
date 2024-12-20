#pragma once

/**
 * @def cast(value, type)
 * @brief A macro to cast a value to a specific type.
 * 
 * @param value The value to be cast.
 * @param type The type to cast the value to.
 * 
 * ---
 */
#define cast(value, type) ((type) value)

/**
 * @def ptr_cast(value, type)
 * @brief Casts a pointer to a specified type.
 * 
 * @param ptr The pointer to be cast.
 * @param type The target type to cast the pointer to.
 * @return A pointer cast to the specified type.
 * 
 * @note This is a type-safe wrapper for pointer casting.
 * 
 * ---
 */
#define ptr_cast(ptr, type) ((type*)(ptr))

/**
 * @def bin_cast(value, type)
 * @brief Casts a pointer value to a specified type.
 * 
 * @param ptr The pointer to be cast.
 * @param type The target type to cast the pointer value to.
 * @return A value to the specified type.
 * 
 * @note This is a non-type-safe wrapper for casting.
 * 
 * ---
 */
#define bin_cast(ptr, type) *((type*)(ptr))
