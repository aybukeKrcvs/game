#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "room.h"

Room *create_room(const char *name) {
    Room *new_room = (Room *)malloc(sizeof(Room));
    if (!new_room) {
        printf("Failed to allocate memory for room.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(new_room->name, name, sizeof(new_room->name) - 1);
    new_room->name[sizeof(new_room->name) - 1] = '\0';
    new_room->item_counter = 0;
    new_room->entity = NULL;
    new_room->up = new_room->down = new_room->left = new_room->right = NULL;
    get_room_description(new_room);

    return new_room;
}

void get_room_description(Room *room) {
    char file_name[NAME_LENGTH];
    sprintf(file_name, "%s.txt", room->name);

    char description[200];
    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("Error opening file %s.\n", file_name);
        strncpy(room->description, "No description available in file.", sizeof(room->description));
        return;
    }

    room->description[0] = '\0';
    while (fgets(description, sizeof(description), file) != NULL) {
        strncat(room->description, description, sizeof(room->description) - strlen(room->description) - 1);
    }

    fclose(file);
}

void display_inventory(Player *player) {
    if (player->item_counter == 0) {
        printf("Your inventory is empty!!");
        return;
    }
    printf("Number of item in your inventory: %d\n", player->item_counter);
    for (int j = 0; j < player->item_counter; j++) {
        printf("Item: %s, value: %d, description: %s\n",
                player->inventory[j]->key,
                player->inventory[j]->value,
                player->inventory[j]->usage);
    }
}

void display_room_list(Room *room) {
    if (room->item_counter == 0) {
        printf("This room is empty!!\n");
        return;
    }
    printf("Number of item in this room: %d\n", room->item_counter);
    for (int j = 0; j < room->item_counter; j++) {
        printf("Item: %s, value: %d, description: %s\n",
                room->list[j]->key,
                room->list[j]->value,
                room->list[j]->usage);
    }
}