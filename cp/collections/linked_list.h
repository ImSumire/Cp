#pragma once

#include <string.h>

#include "../panic.h"
#include "../types/basics.h"
#include "../memory/defer.h"
#include "../memory/safety.h"
#include "../loop.h"

/**
 * @typedef Node
 * @brief Represents an individual element in `List`.
 * It contains a value and a pointer to the next node.
 * 
 * `size = 16, align = 8`
 */
typedef struct Node {
    Any value;
    struct Node* next;
} Node;

/**
 * @typedef List
 * @brief Represents a linked list, it maintains a head and tail
 * pointer for efficient insertions and removals.
 * 
 * `size = 24, align = 8`
 */
typedef struct List {
    Node* head;
    Node* tail;
    i32 size;
    i32 value_size;
} List;

/**
 * @brief Frees the allocated memory of the list, including the nodes and their values.
 * @param self Pointer of the list to be dropped.
 */
void list_drop(List* self) {
    if (!self) return;

    Node* current = self->head;
    Node* next_node;

    while (current != nullptr) {
        next_node = current->next;
        free(current->value);
        free(current);
        current = next_node;
    }

    self->head = nullptr;
    self->tail = nullptr;
    self->size = 0;
}

/**
 * @brief Creates a new empty list with the specified element size.
 * @param value_size The size of the value stored in each list node.
 * @return A newly created list.
 */
List list_new(i32 value_size) {
    return (List) {
        .head = nullptr,
        .tail = nullptr,
        .size = 0,
        .value_size = value_size
    };
}

/**
 * @brief Removes the node at the specified index from the list.
 * @param self The list from which to remove the element.
 * @param index The index of the node to be removed.
 * @note O(n) where n is the index.
 */
void list_remove(List* self, i32 index) {
    if (!self || index < 0 || index >= self->size) {
        fprintf(stderr, "Index out of bounds!\n");
        exit(EXIT_FAILURE);
    }

    Node* to_remove;
    if (index == 0) {
        to_remove = self->head;
        self->head = self->head->next;
        if (self->head == nullptr) {
            self->tail = nullptr;
        }
    } else {
        Node* prev = self->head;
        for range(i, 0, index - 1) {
            prev = prev->next;
        }
        to_remove = prev->next;
        prev->next = to_remove->next;
        if (prev->next == nullptr) {
            self->tail = prev;
        }
    }

    free(to_remove->value);
    free(to_remove);
    self->size--;
}

/**
 * @brief Returns an element from the list at the specified index.
 * @param self   Pointer to the list.
 * @param index  Index of the element to get.
 * @return The element at the given index.
 * @note O(n) where n is the index.
 */
#define list_get(self, index) _list_get(__FILE__, __LINE__, self, index)

/**
 * @brief Internal helper function to get an element from the list.
 * @param file The source file name, used for debugging.
 * @param line The line number, used for debugging.
 * @param self Pointer to the list.
 * @param index Index of the element to get.
 * @return The element at the given index.
 * @note O(n) where n is the index.
 */
Any _list_get(const char* file, i32 line, const List* self, i32 index) {
    if (!self || index < 0 || index >= self->size) {
        _panic(file, line, "Index out of bounds\n");
        return nullptr;
    }

    Node* node = self->head;
    for range(i, 0, index) {
        node = node->next;
    }
    return node->value;
}

/**
 * @brief Adds a new element to the start of the list.
 * @param self Pointer to the list.
 * @param value The element to add.
 * @note O(1)
 */
void list_push(List* self, Any value) {
    Node* new_node = (Node*)safe_malloc(sizeof(Node));
    new_node->value = malloc(self->value_size);  // Allocate memory for the value

    memcpy(new_node->value, value, self->value_size);  // Copy the value into the node
    new_node->next = nullptr;

    if (self->tail == nullptr) {  // If the list is empty
        self->head = self->tail = new_node;
    } else {
        new_node->next = self->head;
        self->head = new_node;
    }
    self->size++;
}

/**
 * @brief Adds a new element to the end of the list.
 * @param self Pointer to the list.
 * @param value The element to add.
 * @note O(1)
 */
void list_push_back(List* self, Any value) {
    Node* new_node = (Node*)safe_malloc(sizeof(Node));
    new_node->value = malloc(self->value_size);  // Allocate memory for the value

    memcpy(new_node->value, value, self->value_size);  // Copy the value into the node
    new_node->next = nullptr;

    if (self->tail == nullptr) {  // If the list is empty
        self->head = self->tail = new_node;
    } else {
        self->tail->next = new_node;
        self->tail = new_node;
    }
    self->size++;
}

/**
 * @brief Inserts a new element into the list at the specified index.
 * @param self Pointer to the list.
 * @param value The element to insert.
 * @param index The index at which to insert the element.
 * @note O(n)
 */
#define list_insert(self, value, index) _list_insert(__FILE__, __LINE__, self, value, index)

/**
 * @brief Internal helper function to insert an element into the list.
 * @param file The source file name, used for debugging.
 * @param line The line number, used for debugging.
 * @param self Pointer to the list.
 * @param value The element to insert.
 * @param index The index at which to insert the element.
 * @note O(n)
 */
void _list_insert(const char* file, i32 line, List* self, Any value, i32 index) {
    if (!self || index < 0 || index > self->size) {
        _panic(file, line, "Index out of bounds\n");
        return;
    }

    Node* new_node = (Node*)safe_malloc(sizeof(Node));
    new_node->value = safe_malloc(self->value_size);
    memcpy(new_node->value, value, self->value_size);

    if (index == 0) {
        new_node->next = self->head;
        self->head = new_node;
        if (self->size == 0) {
            self->tail = new_node;
        }
    } else {
        Node* prev = self->head;
        for range(i, 0, index - 1) {
            prev = prev->next;
        }
        new_node->next = prev->next;
        prev->next = new_node;
        if (new_node->next == nullptr) {
            self->tail = new_node;
        }
    }

    self->size++;
}

/**
 * @brief Creates a new list by applying a transformation function to each element of the original list.
 * @param self Pointer to the original list.
 * @param transform A callable that takes an element and returns a transformed value.
 * @return A new list with the transformed elements.
 */
List list_map(List* self, Callable(transform, Any, const Any)) {
    List new_list = list_new(self->value_size);
    if (!self) return new_list;

    Node* node = self->head;
    while (node != nullptr) {
        Any transformed = transform(node->value);
        list_push_back(&new_list, transformed);
        node = node->next;
        free(transformed);  // Clean up the transformed value after copying
    }
    return new_list;
}

/**
 * @brief Iterates through the list, applying a function to each element.
 * @param self Pointer to the list.
 * @param func A callable that takes an element and performs an operation.
 */
void list_iter(const List* self, Callable(func, void, const Any)) {
    Node* node = self->head;
    while (node != nullptr) {
        func(node->value);
        node = node->next;
    }
}

/**
 * @brief Converts the list to a string representation using a converter function for each element.
 * @param self Pointer to the list.
 * @param converter A callable that converts each element to a string.
 * @return A string representation of the list.
 */
char* list_to_str(const List* self, Callable(converter, char*, const Any)) {
    if (self == nullptr || self->head == nullptr)
        return "[]";
    
    Node* node = self->head;
    i32 length = 7; // "list[]" + \0
    char* temp;
    while (node != nullptr) {
        temp = converter(node->value);
        length += strlen(temp);
        free(temp);

        node = node->next;
        if (node != nullptr) {
            length += 2; // ", "
        }
    }

    char* result = safe_malloc(length);
    char* pos = result;

    *pos++ = 'l';
    *pos++ = 'i';
    *pos++ = 's';
    *pos++ = 't';
    *pos++ = '[';

    node = self->head;

    while (node != nullptr) {
        temp = converter(node->value);
        i32 len = strlen(temp);
        memcpy(pos, temp, len);
        pos += len;
        free(temp);

        node = node->next;
        if (node != nullptr) {
            *pos++ = ',';
            *pos++ = ' ';
        }
    }
    *pos++ = ']';
    *pos = '\0';

    return result;
}

/**
 * @brief Prints the list's string representation using a converter function for each element.
 * @param self Pointer to the list.
 * @param converter A callable that converts each element to a string.
 */

void list_print(const List* self, Callable(converter, char*, const Any)) {
    char* result = list_to_str(self, converter);
    print("%s", result);
    free(result);
}

/**
 * @brief Prints the list's string representation with a newline at the end, 
 * using a converter function for each element.
 * @param self Pointer to the list.
 * @param converter A callable that converts each element to a string.
 */
void list_println(const List* self, Callable(converter, char*, const Any)) {
    char* result = list_to_str(self, converter);
    print("%s\n", result);
    free(result);
}
