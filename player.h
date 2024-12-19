#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
#include "room.h"

typedef struct Player {
    int health;
    int strength;
    int item_counter;
    Item *inventory[INVENTORY_CAPACITY];
    struct Room *current_room;
} Player;

void get_player_info(Player *player);
void display_inventory(Player *player);
void pickup(Player *player, const char *name);
void drop(Player *player, const char *name);
void look(Player *player);
void attack(Player *player, const char *item_name);
void use(Player *player, const char *item_name);
void move(const char *direction);

#endif