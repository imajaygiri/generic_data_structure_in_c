// stack.h
#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
#include <stddef.h>

#define stack_push(stack, __val)                                               \
    do {                                                                       \
        __typeof__(__val) _temp = (__val);                                     \
        Stack_push(stack, &_temp);                                             \
    } while (0)

typedef struct Stack Stack;

Stack *Stack_init(const size_t element_size);
Stack *Stack_init_with_cap(size_t element_size, size_t capacity);
bool Stack_push(Stack *stack, const void *val);
void Stack_destroy(Stack *stack);
void *Stack_peek(Stack *stack);
bool Stack_pop(Stack *stack);
size_t Stack_len(Stack *stack);
bool Stack_is_empty(Stack *stack);
#endif
