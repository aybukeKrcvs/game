#include "player.h"
#include "room.h"
#include <stdio.h>
#include <string.h>

extern Player player;
extern Room *room4_maze ;
extern Item *key;

void get_player_info(Player *player) {
    printf("Player: (health: %d, damage: %d)\n", 
            player->health, player->strength);
}

void display_inventory(Player *player) {
    if (player->item_counter == 0) {
        printf("Your inventory is empty!!");
        return;
    }
    printf("Number of items in your inventory: %d\n", player->item_counter);
    for (int j = 0; j < player->item_counter; j++) {
        printf("Item: %s, value: %d, description: %s\n", 
                player->inventory[j]->key, 
                player->inventory[j]->value, 
                player->inventory[j]->usage);
    }
}

void pickup(Player *player, const char *name) {
    if (strcmp(player->current_room->name, "room2_trap") == 0) {
        player->health = 0;

        char description[780];

        FILE *file = fopen("room2_death.txt", "r");
        if(!file) {
            printf("Error while opening the %s file.\n", "room2_death.txt");
        return;
        }

        while(fgets(description, sizeof(description), file) != NULL) {
            puts(description);
        }
        fclose(file);
        exit(0);
    }

    if (player->item_counter >= INVENTORY_CAPACITY) {
        printf("Inventory is full. You cannot add more items.\n");
        return;
    }

    Room *room = player->current_room;
    for (int j = 0;j < room->item_counter;j++) {
        if (strcmp(room->list[j]->key, name) == 0) {
            /* find the item in room's list and add this item to 
            the player's inventory */
            // memory allocation
            player->inventory[player->item_counter] = (Item*)malloc(sizeof(Item));
            if (!player->inventory[player->item_counter]) {
                printf("Memory allocation is failed!!.\n");
                return;
            }
            // add the item
            player->inventory[player->item_counter] = room->list[j];
            player->item_counter++;
            printf("Item '%s' has added to your inventory.\n", name);

            //remove the item from the room
            for(int k = j;k < room->item_counter-1;k++) {
                room->list[k] = room->list[k+1];
            }
            room->list[room->item_counter - 1] = NULL;
            room->item_counter--;
            return;
        }
    }

    printf("There is no such '%s' item in this room.\n", name);
}

void drop(Player *player, const char *name) {
    if (player->item_counter == 0) {
        printf("You inventory is empty. There is no item to drop.\n");
        return;
    }

    Room *room = player->current_room;
    for(int j = 0;j < player->item_counter;j++) {
        if (strcmp(player->inventory[j]->key, name) == 0) {
            if (room->item_counter >= INVENTORY_CAPACITY) {
                printf("The room is already full, it cannot hold more items.\n");
                return;
            }
            room->list[room->item_counter] = (Item *)malloc(sizeof(Item));
            if(!room->list[room->item_counter]) {
                printf("Memory allocation is failed!!.\n");
                return;
            }

            room->list[room->item_counter] = player->inventory[j];
            room->item_counter++;
            printf("Item '%s' has already dropped into the room.\n", name);

            free(player->inventory[j]);

            for(int k = j;k < player->item_counter - 1;k++) {
                player ->inventory[k] = player->inventory[k+1];
            }
            player->inventory[player->item_counter - 1] = NULL;
            player->item_counter--;
            return;
        }
    }
}

void look(Player *player) {
    Room *current = player->current_room;
    // check if current room exists in any case to avoid error
    if (current) {
        get_room_description(current);

        printf("Room: %s\n", current->name);
        printf("Description: %s\n", current->description);
        printf("\n");
        display_room_list(player->current_room);

        if(current->entity) {
            get_entity_info(current->entity);
        }else {
            printf("There is no entity in this room.\n");
        }

        printf("\n");
        if (strcmp(player->current_room->name, "room4_maze") == 0) {
            
            if (initialize_item(&key, "key", 1, "key to open 7th door") == 0) {
                room4_maze->list[room4_maze->item_counter] = key;
                room4_maze->item_counter++;
            }

            room4();  
        }

    }else {
        printf("Invalid room!\n");
    }
}

void attack(Player *player, const char *item_name) {
    Entity *entity = player->current_room->entity;

    if(entity == NULL) {
        printf("There is no enemy in this room to attack!!\n");
        return;
    }

    Item *sword;
    for(int j = 0;j < player->item_counter;j++) {
        if (strcmp(player->inventory[j]->key, item_name) == 0) {
            sword = player->inventory[j];
        }
    }
    if (sword == NULL) {
        printf("You do not have such a sword to fight.\n");
        return;
    }

    printf("Your health: %d, strength: %d, sword's average damage: %d\n",
            player->health, player->strength, sword->value);
    printf("%s entity's health: %d, damage: %d\n",
            entity->name, entity->health, entity->damage);
    printf("\nFighting is starting. ARE YOU READDDDYYYY!!!??\n\n");

    while(player->health > 0 && entity->health > 0) {
        int player_damage = player->strength * random_damage(sword->value);
        entity->health -= player_damage;
        printf("Your total damage: %d, player health: %d, %s's health: %d\n",
                player_damage, player->health, entity->name, entity->health);
        if (entity->health <= 0) {
            printf("Congratulations! You defeated the %s.\n", entity->name);
            player->current_room->entity = NULL;
            return;
        }

        player->health -=entity->damage;
        printf("%s's total damage: %d, player health: %d, %s's health: %d\n",
                entity->name, entity->damage, player->health, entity->name, entity->health);
        if (player->health <= 0) {
            printf("GAME OVER! You have been defeated by %s.\n", entity->name);
            exit(0);
        }
    }

}

void use(Player *player, const char *item_name) {

    if (strcmp(item_name, "kimiz") == 0) {
        printf("You use a Kimiz! Your health is restored.\n");
        player->health += 40; 
        if (player->health > 100) player->health = 100; 
    }
    else if (strcmp(item_name, "heart_poiton") == 0) {
        printf("You use a Heart Poiton! Your health is restored and increase your health bound.\n");
        player->health += 150;
    }
    else if (strcmp(item_name, "baklava") == 0) {
        printf("You use a Baklava! Your health is restored.\n");
        player->health += 30; 
        if (player->health > 100) player->health = 100;
    }
    else if (strcmp(item_name, "delight") == 0) {
        printf("You use a Turkish Delight! Your health is restored.\n");
        player->health += 20; 
        if (player->health > 100) player->health = 100;
    }
    else if (strcmp(item_name, "poiton") == 0) {
        printf("You use a Strength Poiton! Your strength is increased.\n");
        player->strength += 20; 
    }
    else {
        printf("You can't use this item.\n");
    }

}

void move(const char *direction) {
    Room *next = NULL;

    //direct and initialize the possible next room to wanted direction
    if (strcmp(direction, "up") == 0) {
        next = player.current_room->up;
    }else if (strcmp(direction, "right") == 0) {
        next = player.current_room->right;
    }else if (strcmp(direction, "down") == 0) {
        next = player.current_room->down;
    }else if (strcmp(direction, "left") == 0) {
        next = player.current_room->left;
    }else {
        printf("Invalid or unproper direction. Type 'up', 'right', 'down' or 'left'.\n");
        return;
    }

    /* If the room player want to go to is in the room the player is in,
     update the player's current room.  */
    if (strcmp(next->name, "room7_tepegoz") == 0) {
        int has_key = 0;
        for (int i = 0; i < player.item_counter; i++) {
            if (strcmp(player.inventory[i]->key, "key") == 0) {
                has_key = 1;
                break;
            }
        }

        if (!has_key) {
            printf("You need the key to enter the next room! Find the key first.\n");
            return; // Prevent moving without the key
        }
    }
    if (next) {
        player.current_room = next;
        printf("You moved to %s room.\n", direction);     

    }else {
        printf("There is no room %s there!!\n", direction);
    }
}