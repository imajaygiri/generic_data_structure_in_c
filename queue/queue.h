#ifndef QUEUE_H
#define QUEUE_H
#include <list.h>
#include <stddef.h>
#define let __auto_type
typedef struct Queue Queue;

#define queue_enque(queue, data)                                               \
    do {                                                                       \
        __typeof__((data)) _data = data;                                       \
        Queue_enque(queue, &_data);                                            \
    } while (0)

Queue *Queue_init(size_t element_size);
void Queue_enque(Queue *queue, const void *data);
void Queue_deque(Queue *queue);
void *Queue_peek(Queue *queue);
size_t Queue_len(Queue *queue);
List *Queue_list(Queue *queue);
#endif
