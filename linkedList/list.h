#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

#define list_is_contain(list, key)                                             \
    ({                                                                         \
        __typeof__(key) _key = (key);                                          \
        List_is_contain((list), &_key);                                        \
    })
#define list_push_back(list, data)                                             \
    do {                                                                       \
        __typeof__((data)) _data = (data);                                     \
        List_push_back(list, &_data);                                          \
    } while (0)

#define list_push_front(list, data)                                            \
    do {                                                                       \
        __typeof__((data)) _data = (data);                                     \
        List_push_front(list, &_data);                                         \
    } while (0)

typedef struct List List;
typedef struct ListNode ListNode;

typedef struct {
    List *list;
    size_t curr_idx;
    ListNode *indexNode;
} Next;

ListNode *List_find_node(List *list, const void *key);
List *List_init(size_t element_size);
void List_push_front(List *list, const void *data);
void List_push_back(List *list, const void *data);
Next List_create_iter(List *list);
void *List_next(Next *it);
bool List_is_contain(List *list, const void *key);
bool List_pop_back(List *list);
void *List_peek_back(List *list);
void *List_peek_front(List *list);
bool List_is_empty(List *list);
bool List_pop_front(List *list);
void List_destroy(List *list);
bool List_delete_node(List *list, const void *key);
void List_print(List *list, void (*print_fxn)(const void *data));
void print_fxn(const void *data);
#endif
