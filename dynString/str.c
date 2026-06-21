// str.c
#include "str.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define let __auto_type
#define LOG_ERROR(fmt) (fprintf(stderr, "%s:%d " fmt "\n", __FILE__, __LINE__))

struct DynStr {
    char *data;
    size_t capicity;
    size_t len;
};

DynStr *DynStr_init_with_capacity(size_t capacity) {
    if (capacity < 0 || capacity == 0) {
        LOG_ERROR("capacity is invalid");
        return NULL;
    }
    DynStr *dstr = malloc(sizeof(DynStr));
    if (!dstr) {
        LOG_ERROR("Error initing dynstr");
        return NULL;
    }

    dstr->data = malloc(sizeof(char) * capacity);
    if (!dstr->data) {
        free(dstr);
        LOG_ERROR("Error allocating memory for dstr");
        return NULL;
    }
    dstr->len = 0;
    dstr->capicity = capacity;

    return dstr;
}

DynStr *DynStr_init() { return DynStr_init_with_capacity(1); }

void DynStr_append(DynStr *dynstr, const char *s) {
    if (dynstr->len == dynstr->capicity) {
        // realloc memory
        dynstr->data =
            realloc(dynstr->data, sizeof(char) * dynstr->capicity * 2);
        dynstr->capicity *= 2;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        dynstr->data[i] = s[i];
        dynstr->len++;
    }
    dynstr->data[dynstr->len] = '\0';
}

void DynStr_append_char(DynStr *dynstr, char ch) {
    if (dynstr->len == dynstr->capicity) {
        // realloc memory
        dynstr->data =
            realloc(dynstr->data, sizeof(char) * dynstr->capicity * 2);
        dynstr->capicity *= 2;
    }

    dynstr->data[dynstr->len++] = ch;
    dynstr->data[dynstr->len] = '\0';
}
char *DynStr_get_c_char(DynStr *dynstr) {
    if (!dynstr) {
        LOG_ERROR("ERROR: dynstr is null\n");
    }
    return dynstr->data;
}

void DynStr_destroy(DynStr *dynstr) {
    free(dynstr->data);
    free(dynstr);
}

char DynStr_pop_back(DynStr *dynstr) {
    char ch = (dynstr->data[dynstr->len - 1]);
    dynstr->len--;
    return ch;
}

unsigned char DynStr_is_empty(DynStr *dynstr) { return dynstr->len == 0; }

// [a, b, c, d]

int main(void) {
    let str = DynStr_init();
    char *s = "hello wolrd";
    for (int i = 0; s[i] != '\0'; i++) {
        DynStr_append_char(str, s[i]);
    }

    while (!DynStr_is_empty(str)) {
        printf("%c\n", DynStr_pop_back(str));
    }
    return 0;
}
