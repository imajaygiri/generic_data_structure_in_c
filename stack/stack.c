// stack.c
#include "stack.h"
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
    void *data;
    size_t len;
    size_t cap;
    size_t element_size;
};

Stack *Stack_init_with_cap(const size_t element_size, size_t capacity) {
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) {
        perror("Error allocating memory in init Stack");
        exit(-1);
    }
    stack->cap = capacity > 0 ? capacity : 1;
    stack->data = malloc(element_size * stack->cap);
    if (!stack->data) {
        perror("Error allocating memory for stack");
        exit(-1);
    }
    stack->len = 0;
    stack->element_size = element_size;
    return stack;
}

Stack *Stack_init(const size_t element_size) {
    return Stack_init_with_cap(element_size, 1);
}

bool Stack_push(Stack *stack, const void *val) {
    if (stack->len == stack->cap) {
        size_t new_cap = stack->cap * 2;
        void *newData = realloc(stack->data, stack->element_size * new_cap);

        if (newData != NULL) {
            stack->data = newData;
            stack->cap = new_cap;
        } else {
            fprintf(stderr, "Error allocating new memory for Stack %s: %d\n",
                    __FILE__, __LINE__);
            return false;
        }
    }

    char *dst = (char *)stack->data + stack->element_size * stack->len;
    memcpy(dst, val, stack->element_size);
    stack->len++;
    return true;
}

void Stack_destroy(Stack *stack) {
    free(stack->data);
    free(stack);
}

void *Stack_peek(Stack *stack) {
    if (stack->len < 1)
        return NULL;
    char *target = (char *)stack->data + stack->element_size * (stack->len - 1);
    return target;
}

bool Stack_pop(Stack *stack) {
    if (stack->len < 1)
        return false;
    stack->len--;
    return true;
}

size_t Stack_len(Stack *stack) { return stack->len; }

bool Stack_is_empty(Stack *stack) { return stack->len == 0; }
