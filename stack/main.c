#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#define let __auto_type

typedef struct {
    Stack *stack1;
    Stack *stack2;
} MyQueue;

static void transer(Stack *dst, Stack *src) {
    while (!Stack_is_empty(src)) {
        let val = Stack_peek(src);
        Stack_push(dst, val);
        Stack_pop(src);
    }
}

MyQueue *myQueueCreate() {
    let queue = (MyQueue *)malloc(sizeof(MyQueue));
    if (!queue) {
        perror("Error Initing Queueu");
        return NULL;
    }
    queue->stack1 = Stack_init(sizeof(int));
    queue->stack2 = Stack_init(sizeof(int));
    return queue;
}

void myQueuePush(MyQueue *obj, int x) { stack_push(obj->stack1, x); }

int myQueuePop(MyQueue *obj) {
    if (Stack_is_empty(obj->stack2)) {
        for (let i = 0; i < Stack_len(obj->stack1); i++) {
            let const val = Stack_peek(obj->stack1);
            Stack_push(obj->stack2, val);
            Stack_pop(obj->stack1);
        }
    }
    let poped_val = Stack_peek(obj->stack2);
    Stack_pop(obj->stack2);
    return *(int *)poped_val;
}

int myQueuePeek(MyQueue *obj) {
    if (Stack_is_empty(obj->stack2)) {
        for (let i = 0; i < Stack_len(obj->stack1); i++) {
            let const val = Stack_peek(obj->stack1);
            Stack_push(obj->stack2, val);
            Stack_pop(obj->stack1);
        }
    }
    let poped_val = Stack_peek(obj->stack2);
    return *(int *)poped_val;
}

bool myQueueEmpty(MyQueue *obj) {
    if (Stack_is_empty(obj->stack1) && Stack_is_empty(obj->stack2))
        return true;
    else
        return false;
}

void myQueueFree(MyQueue *obj) {
    Stack_destroy(obj->stack1);
    Stack_destroy(obj->stack2);
    free(obj);
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 * int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
*/

int main(void) {

    let queue = myQueueCreate();
    myQueuePush(queue, 10);
    myQueuePush(queue, 20);
    let val = myQueuePop(queue);
    printf("poped val: %d\n", val);
    val = myQueuePop(queue);
    printf("poped val: %d\n", val);

    myQueuePush(queue, 20);
    myQueuePush(queue, 5);
    val = myQueuePop(queue);
    printf("poped val: %d\n", val);
    val = myQueuePeek(queue);
    printf("peek val: %d\n", val);
    return 0;
}
