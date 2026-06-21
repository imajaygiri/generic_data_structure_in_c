#include "vec.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOG_ERROR(fmt)                                                         \
    do {                                                                       \
        fprintf(stderr, "%s: %d " fmt "\n", __FILE__, __LINE__);               \
    } while (0)

#define vec_push_back(vec, key)                                                \
    do {                                                                       \
        __typeof__(key) _key;                                                  \
        Vec_push_back(&_key);                                                  \
    } while (0)

struct Vec {
    void *data;
    size_t len;
    size_t cap;
    size_t element_size;
};

Vec *vec_init_with_cap(size_t cap, size_t element_size) {
    if (element_size == 0) {
        LOG_ERROR("element_size of == 0 is not supported");
        return NULL;
    }

    Vec *vec = malloc(sizeof(Vec));
    if (!vec) {
        LOG_ERROR("Error initing vec");
        return NULL;
    }

    if (cap == 0) {
        vec->cap = 1;
    } else {
        vec->cap = cap;
    }
    vec->len = 0;
    vec->data = malloc(element_size * vec->cap);
    vec->element_size = element_size;
    if (!vec->data) {
        LOG_ERROR("Error allocating space for data in init vec");
        free(vec);
        return NULL;
    }
    return vec;
}

Vec *vec_init(size_t element_size) {
    if (element_size == 0) {
        LOG_ERROR("element_size of == 0 is not supported");
        return NULL;
    }
    return vec_init_with_cap(1, element_size);
}

bool Vec_push_back(Vec *vec, const void *key) {
    if (!vec) {
        LOG_ERROR("vec can not be NULL");
        return false;
    }
    if (vec->len == vec->cap) {
        void *new_ptr = realloc(vec->data, vec->element_size * vec->cap * 2);
        if (!new_ptr) {
            LOG_ERROR("Error reallocating vec");
            return false;
        }
    }
    char *target = (char *)vec->data + vec->len * vec->element_size;
    memcpy(target, key, vec->element_size);
    vec->len++;
    return true;
}
void *Vec_back(Vec *vec) {
    if (!vec) {
        LOG_ERROR("Error vec is NULL");
        return NULL;
    }

    return (char *)vec->data + (vec->len - 1) * vec->element_size;
}
void *Vec_front(Vec *vec) {
    if (!vec) {
        LOG_ERROR("Error vec is NULL");
        return NULL;
    }

    if (vec->len == 0) {
        LOG_ERROR("Error vec is empty");
        return NULL;
    }
    return (char *)vec->data;
}
size_t Vec_len(Vec *vec) {
    if (!vec) {
        LOG_ERROR("Error vec is NULL");
        return NULL;
    }
    return vec->len;
}
size_t Vec_capacity(Vec *vec) {
    if (!vec) {
        LOG_ERROR("Error vec is NULL");
        return NULL;
    }
    return vec->cap;
}
void *Vec_get(Vec *vec, size_t idx) {
    if (!vec) {
        LOG_ERROR("Error vec is NULL");
        return NULL;
    }

    if (idx < 0 || idx >= vec->len) {
        LOG_ERROR("Error check index");
        return NULL;
    }
    return (char *)vec->data + vec->element_size * idx;
}
void Vec_reverse(Vec *vec, int (*cmp)(const void *e1, const void *e2));

bool Vec_is_contain(Vec *vec, const void *key) {
    for (int i = 0; i < vec->len; i++) {
        char *target = (char *)vec->data + vec->element_size * i;
        if (memcmp(key, target, vec->element_size) == 0) {
            return true;
        }
    }
    return false;
}
bool Vec_remove_element(Vec *vec, const void *key) {
    if (!Vec_is_contain(vec, key)) {
        LOG_ERROR("Element does not exist in vec");
        return false;
    }
    
}
void Vec_sort(Vec *vec, int (*cmp)(const void *e1, const void *e2));
void Vec_destroy(Vec *vec) {
    if (!vec) {
        return;
    }
    free(vec->data);
    free(vec);
    return;
}
