#include "queue.h"
#include <list.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define LOG_ERROR(fmt)                                                         \
    fprintf(stderr, "[ERROR] %s:%d: " fmt "\n", __FILE__, __LINE__)

#define CHECK_QUEUE_NULL_ERROR(queue)                                          \
    {                                                                          \
        if (!(queue)) {                                                        \
            LOG_ERROR("Queue can not be null");                                \
        }                                                                      \
    }

struct Queue {
    List *list;
};

Queue *Queue_init(size_t element_size) {
    if (element_size < 0) {
        LOG_ERROR("Element size can not be negative");
        return NULL;
    }
    Queue *queue = malloc(sizeof(Queue));
    if (!queue) {
        LOG_ERROR("Error initing Queue");
        return NULL;
    }
    queue->list = List_init(element_size);
    if (!queue->list) {
        LOG_ERROR("Error initing Queue");
        free(queue);
        return NULL;
    }
    return queue;
}

void Queue_enque(Queue *queue, const void *data) {
    CHECK_QUEUE_NULL_ERROR(queue);
    List_push_front(queue->list, data);
}

void Queue_deque(Queue *queue) {
    CHECK_QUEUE_NULL_ERROR(queue);
    bool result = List_pop_back(queue->list);
    if (!result) {
        LOG_ERROR("Dequeu failed , Some error occured");
        return;
    }
}

void *Queue_peek(Queue *queue) {
    CHECK_QUEUE_NULL_ERROR(queue);
    return List_peek_back(queue->list);
}
size_t Queue_len(Queue *queue) {
    CHECK_QUEUE_NULL_ERROR(queue);
    return List_len(queue->list);
}
List *Queue_list(Queue *queue) { return queue->list; }
