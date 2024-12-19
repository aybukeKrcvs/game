#ifndef ROOM_H
#define ROOM_H

#include "item.h"
#include "entity.h"
#include "player.h"

#define INVENTORY_CAPACITY 12

typedef struct Room {
    char name[NAME_LENGTH];
    char description[1000];
    Item *list[INVENTORY_CAPACITY];
    int item_counter;
    Entity *entity;
    struct Room *up;
    struct Room *right;
    struct Room *down;
    struct Room *left;
} Room;

Room *create_room(const char *name);
void get_room_description(Room *room);
void display_room_list(Room *room);
void display_inventory(Player *player);

#endif
