#ifndef ITEM_H
#define ITEM_H

#define NAME_LENGTH 30

typedef struct Item {
    char key[NAME_LENGTH];
    int value;
    char usage[30];
} Item;

int initialize_item(Item **item_ptr, const char *key, int value, const char *usage);

#endif