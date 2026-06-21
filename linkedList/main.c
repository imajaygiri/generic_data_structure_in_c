#include "list.h"
#include <stdio.h>
#define let __auto_type

void print_fxn(const void *data) { printf(" %d ", *(int *)data); }

int main() {
    let list = List_init(sizeof(int));

    list_push_back(list, 1);
    list_push_back(list, 2);
    list_push_back(list, 3);
    list_push_back(list, 4);
    list_push_back(list, 5);

    // List_print(list, print_fxn);
    for(int i=1; i<5; i++){
        print_fxn(List_at_index(list, i));
    }
    return 0;
}

