#pragma once


#include <string.h>

#include "../panic.h"
#include "../types/basics.h"
#include "../memory/defer.h"
#include "../memory/safety.h"


typedef struct Node {
    untyped value;
    struct Node* next;
} Node;


typedef struct List {
    Node* head;
    Node* tail;
    i32 size;
    i32 value_size;
} List;

void list_drop(List* self) {
    if (!self) return;

    Node* current = self->head;
    Node* next_node;

    while (current != nullptr) {
        next_node = current->next;
        free(current->value);  // Free the value
        free(current);
        current = next_node;
    }

    self->head = nullptr;
    self->tail = nullptr;
    self->size = 0;
}

List list_new(i32 value_size) {
    return (List) {
        .head = nullptr,
        .tail = nullptr,
        .size = 0,
        .value_size = value_size
    };
}

void list_remove(List* self, i32 index) {
    // O(n)
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
        for (i32 i = 0; i < index - 1; i++) {
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

#define list_get(self, index) _list_get(__FILE__, __LINE__, self, index)

untyped _list_get(const char* file, i32 line, const List* self, i32 index) {
    // O(n)
    if (!self || index < 0 || index >= self->size) {
        _panic(file, line, "Index out of bounds\n");
        return nullptr;
    }

    Node* node = self->head;
    for (i32 i = 0; i < index; i++) {
        node = node->next;
    }
    return node->value;
}

void list_push(List* self, untyped value) {
    // DEV: to test
    // O(1)
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

void list_push_back(List* self, untyped value) {
    // O(1) thanks to self.tail
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

#define list_insert(self, value, index) _list_insert(__FILE__, __LINE__, self, value, index)

void _list_insert(const char* file, i32 line, List* self, untyped value, i32 index) {
    // O(n)
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
        for (i32 i = 0; i < index - 1; i++) {
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

List list_map(List* self, Callable(transform, untyped, const untyped)) {
    List new_list = list_new(self->value_size);
    if (!self) return new_list;

    Node* node = self->head;
    while (node != nullptr) {
        untyped transformed = transform(node->value);
        list_push_back(&new_list, transformed);
        node = node->next;
        free(transformed);  // Clean up the transformed value after copying
    }
    return new_list;
}

#define list_iter(self, func) _list_iter(__FILE__, __LINE__, self, func)

void _list_iter(const char* file, i32 line, const List* self, Callable(func, void, const untyped)) {
    if (!self) {
        _panic(file, line, "List is null\n");
        return;
    }

    Node* node = self->head;
    while (node != nullptr) {
        func(node->value);  // Apply the function to each element
        node = node->next;
    }
}

char* list_to_str(const List* self, Callable(converter, char*, const untyped)) {
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

void list_print(const List* self, Callable(converter, char*, const untyped)) {
    char* result = list_to_str(self, converter);
    print("%s", result);
    free(result);
}

void list_println(const List* self, Callable(converter, char*, const untyped), ...) {
    char* result = list_to_str(self, converter);
    print("%s\n", result);
    free(result);
}
