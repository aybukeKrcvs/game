#include <stdio.h>
#include <string.h>
#include "item.h"

int initialize_item(Item **item_ptr, const char *key, int value, const char *usage) {
    *item_ptr = (Item *)malloc(sizeof(Item));
    if (*item_ptr == NULL) {
        printf("Memory allocation failed for item.\n");
        return -1;
    }

    strncpy((*item_ptr)->key, key, sizeof((*item_ptr)->key));
    (*item_ptr)->key[sizeof((*item_ptr)->key) - 1] = '\0';
    (*item_ptr)->value = value;

    if (usage) {
        strncpy((*item_ptr)->usage, usage, sizeof((*item_ptr)->usage));
        (*item_ptr)->usage[sizeof((*item_ptr)->usage) - 1] = '\0';
    } else {
        (*item_ptr)->usage[0] = '\0';
    }
    return 0;
}
