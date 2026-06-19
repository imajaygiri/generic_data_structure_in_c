#include "list.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    void *data;
    struct ListNode *next;
    struct ListNode *prev;
};
struct List {
    ListNode *head;
    ListNode *tail;
    size_t len;
    size_t element_size;
};

static ListNode *create_node(List *list, const void *data) {
    ListNode *node = malloc(sizeof(ListNode));
    if (!node) {
        perror("Error creating node");
        return NULL;
    }
    node->data = malloc(list->element_size);
    if (!node->data) {
        perror("Error creatign space for listNode");
        free(node);
        return NULL;
    }
    node->next = NULL;
    node->prev = NULL;
    memcpy(node->data, data, list->element_size);
    return node;
}

List *List_init(size_t element_size) {
    List *list = malloc(sizeof(List));
    if (!list) {
        perror("Error creating list");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->element_size = element_size;
    list->len = 0;
    return list;
}

void List_push_front(List *list, const void *data) {
    if (list->head == NULL) {
        list->tail = list->head = create_node(list, data);
        list->len++;
        return;
    }

    ListNode *node = create_node(list, data);
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
    list->len++;
    return;
}

void List_push_back(List *list, const void *data) {
    if (list->head == NULL) {
        list->tail = list->head = create_node(list, data);
        list->len++;
        return;
    }

    ListNode *node = create_node(list, data);
    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
    list->len++;
    return;
}

Next List_create_iter(List *list) {
    Next next;
    if (!list) {
        perror("Error list can not be NULL");
        exit(-1);
    }
    next.curr_idx = 0;
    next.list = list;
    next.indexNode = list->head;
    return next;
}

// void *List_next(Next *NextObj) {
//     if (!NextObj) {
//         perror("Next can't be null");
//         return NULL;
//     }
//
//     if (NextObj->curr_idx > NextObj->list->len) {
//         return NULL;
//     }
//     void *data = NextObj->indexNode->data;
//     NextObj->indexNode = NextObj->indexNode->next;
//     NextObj->curr_idx++;
//     return data;
// }

void *List_next(Next *it) {
    if (!it) {
        return NULL;
    }

    if (!it->indexNode) {
        return NULL;
    }

    void *data = it->indexNode->data;
    it->indexNode = it->indexNode->next;
    it->curr_idx++;

    return data;
}

bool List_is_contain(List *list, const void *key) {
    Next it = List_create_iter(list);
    void *data = NULL;
    while ((data = List_next(&it)) != NULL) {
        if (memcmp(data, key, list->element_size) == 0) {
            return true;
            break;
        }
    }
    return false;
}

bool List_pop_back(List *list) {
    // delete tail
    if (!list) {
        perror("list is null");
        return false;
    }

    if (list->len == 0) {
        perror("Error list is empty");
        return false;
    }

    if (list->len == 1) {
        ListNode *temp_node = list->head;
        list->head = list->tail = NULL;
        free(temp_node->data);
        free(temp_node);
        list->len--;
        return true;
    }

    ListNode *temp_tail = list->tail;
    temp_tail->prev->next = NULL;
    list->tail = temp_tail->prev;
    free(temp_tail->data);
    free(temp_tail);
    list->len--;
    return true;
}

void *List_peek_back(List *list) {

    if (!list) {
        perror("list can not be null");
        return NULL;
    }
    if (list->len == 0) {
        return NULL;
    }
    return list->tail->data;
}

void *List_peek_front(List *list) {
    if (list->len == 0) {
        return NULL;
    }
    return list->head->data;
}

bool List_is_empty(List *list) { return list->len == 0; }

bool List_pop_front(List *list) {

    if (!list) {
        perror("list can not be null");
        return false;
    }

    if (list->len == 0) {
        perror("Error list is empty");
        return false;
    }

    if (list->len == 1) {
        ListNode *temp_node = list->head;
        list->head = list->tail = NULL;
        free(temp_node->data);
        free(temp_node);
        list->len--;
        return true;
    }

    ListNode *temp_head = list->head;
    list->head = list->head->next;
    temp_head->next->prev = NULL;
    free(temp_head->data);
    free(temp_head);
    list->len--;
    return true;
}

// ListNode* List_delete_node(List* list, ListNode* key){
//
// }

void List_destroy(List *list) {
    ListNode *temp = list->head;

    while (temp) {
        ListNode *next = temp->next;
        free(temp->data);
        free(temp);
        temp = next;
    }
}

ListNode *List_find_node(List *list, const void *key) {
    // returns first found node
    ListNode *temp = list->head;
    while (temp) {
        if (memcmp(key, temp->data, list->element_size) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

bool List_delete_node(List *list, const void *key) {

    if (!list) {
        perror("Can not delete NULL list");
        return false;
    }

    ListNode *node = List_find_node(list, key);
    if (!node) {
        return false;
    }

    if (list->head == node) {
        return List_pop_front(list);
    }

    if (list->tail == node) {
        return List_pop_back(list);
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->data = NULL;
    free(node);
    return true;
}

void List_print(List *list, void (*_print_fxn_)(const void *data)) {
    Next it = List_create_iter(list);
    void *data = NULL;
    printf("[");
    while ((data = List_next(&it)) != NULL) {
        _print_fxn_(data);
    }
    printf("]");
}

size_t List_len(List *list) {
    if (!list) {
        perror("Error list can not be null");
        return 0;
    }
    return list->len;
}
