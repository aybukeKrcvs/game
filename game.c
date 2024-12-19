#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "player.h"
#include "room.h"
#include "item.h"
#include "entity.h"

#define MAX_HEALTH 100
#define DEFAULT_STRENGTH 3
#define SAVE_DIR "saves/"
#define MAX_SAVES 10
#define NAME_LENGHT 30

// my global variables
Player player;
Player *player_ptr = &player;
Room *room1_start, *room2_trap, *room3_gulyabani, *room4_maze;
Room *room5_storage, *room6_hinkirmunkur, *room7_tepegoz;
Item *key;

void list_saves() {
    printf("Available saved games:\n");

    FILE *file;
    char save_name[256];
    int save_count = 0;

    file = fopen(SAVE_DIR "saves.txt", "r");
    if (file == NULL) {
        printf("No saves available.\n");
        return;
    }

    while (fgets(save_name, sizeof(save_name), file)) {
        printf("- %s", save_name);
        save_count++;
    }

    fclose(file);

    if (save_count == 0) {
        printf("No saves available.\n");
    }
}

void save_game(const char *filepath) {
    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s%s", SAVE_DIR, filepath);

    FILE *fp = fopen(full_path, "w");
    if (fp == NULL) {
        printf("Failed to save the game to %s\n", full_path);
        return;
    }

    // Save the player's state
    fprintf(fp, "health:%d\nstrength:%d\nitem_count:%d\n",
            player_ptr->health, player_ptr->strength, player_ptr->item_counter);

    for (int i = 0; i < player_ptr->item_counter; i++) {
        fprintf(fp, "item:%s:%d:%s\n",
                player_ptr->inventory[i]->key,
                player_ptr->inventory[i]->value,
                player_ptr->inventory[i]->usage);
    }

    fclose(fp);
    printf("Game saved to %s\n", full_path);
}

void load_game(const char *filepath) {
    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s%s", SAVE_DIR, filepath);

    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        printf("Failed to load the game from %s\n", full_path);
        return;
    }

    // Reset player's state
    player_ptr->health = MAX_HEALTH;
    player_ptr->strength = DEFAULT_STRENGTH;
    player_ptr->item_counter = 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char key[NAME_LENGHT], usage[30];
        int value;

        if (sscanf(line, "health:%d", &player_ptr->health) == 1) continue;
        if (sscanf(line, "strength:%d", &player_ptr->strength) == 1) continue;
        if (sscanf(line, "item_count:%d", &player_ptr->item_counter) == 1) continue;

        if (sscanf(line, "item:%[^:]:%d:%s", key, &value, usage) == 3) {
            Item *item;
            initialize_item(&item, key, value, usage);
            player_ptr->inventory[player_ptr->item_counter++] = item;
        }
    }

    fclose(file);
    printf("Game loaded from %s\n", full_path);
}

void room4() {
    char description[1200];

    FILE *file = fopen("room4_print.txt", "r");
    if(!file) {
         printf("Error while opening the %s file.\n", "room2_death.txt");
    return;
    }

    while(fgets(description, sizeof(description), file) != NULL) {
        puts(description);
    }
    fclose(file);
    printf("\n");
}

int random_damage(int min) {
    int max = min + (int)(min / 2);
    int damage = min + rand() % (max - min + 1);
    return damage;
}

void get_command_descriptions() {
    char filename[] = "game_command_description.txt";
    char description[1500];
    FILE *file;

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("error while opening the %s file", filename);
        return;
    }

    printf("\n");
    while (fgets(description, sizeof(description), file) != NULL) {
        printf("%s", description);
    }
    fclose(file);
    printf("\n");
    return;
}

void get_map() {
    char filename[] = "map.txt";
    char description[80];
    FILE *file;

    file = fopen("map.txt", "r");

    if(file == NULL) {
        printf("Error while opening the %s file.\n", filename);
        return;
    }

    printf("\n");
    while (fgets(description, sizeof(description), file) != NULL) {
        printf("%s", description);
    }
    fclose(file);
    printf("\n");
    return;
}

void in_game_commands_loop() {
    char input[256];
    char action[256];
    char argument[256];
    printf("\nWELCOME TO DEDE KORKUT ADVENTURES!!!, type 'help' to learn commands.\n\n");

    while (1) {
        printf(">> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        int words = sscanf(input, "%s %s", action, argument);

        if (words == 1) {
            // Handle single-word commands
            if (strcmp(action, "look") == 0) {
                look(player_ptr);
            }else if (strcmp(action, "inventory") == 0) {
                display_inventory(player_ptr);
            }else if (strcmp(action, "status") == 0) {
                get_player_info(player_ptr);
            }else if (strcmp(action, "help") == 0) {
                get_command_descriptions();
            }else if (strcmp(action, "map") == 0) {
                get_map();
            }else if (strcmp(action, "exit") == 0) {
                printf("That was a good game. Exiting the game. Goodbye!\n");
                exit(0);
            }else if(strcmp(action, "list") == 0) {
                list_saves();
            } else {
                printf("Unknown command: %s\n", action);
            }
        } else if (words == 2) {
            // Handle two-word commands (e.g., move up)
            if (strcmp(action, "move") == 0) {
                move(argument);
            } else if (strcmp(action, "pickup") == 0) {
                pickup(player_ptr, argument);
            }else if (strcmp(action, "drop") == 0) {
                drop(player_ptr, argument);
            }else if (strcmp(action, "attack") == 0) {
                attack(player_ptr, argument);
            }else if (strcmp(action, "use") == 0) {
                use(player_ptr, argument);
            }else if (strcmp(action, "save") == 0) {
                save_game(argument);
            }else if (strcmp(action, "load") == 0) {
                load_game(argument);
            }else {
                printf("Unknown command: %s\n", action);
            }
        } else {
            // Invalid input or empty command
            printf("Unknown command.\n");
        }
    }

}

void default_values() {
    player_ptr->health = MAX_HEALTH;
    player_ptr->strength = DEFAULT_STRENGTH;
    player_ptr->item_counter = 0;

    room1_start = create_room("room1_start");
    room2_trap = create_room("room2_trap");
    room3_gulyabani = create_room("room3_gulyabani");
    room4_maze = create_room("room4_maze");
    room5_storage = create_room("room5_storage");
    room6_hinkirmunkur = create_room("room6_hinkirmunkur");
    room7_tepegoz = create_room("room7_tepegoz");

    room1_start->down = room1_start->left = NULL;
    room1_start->right = room2_trap;
    room1_start->up = room3_gulyabani;

    room2_trap->up = room2_trap->right = room2_trap->down = NULL;
    room2_trap->left = room1_start;

    room3_gulyabani->right = NULL;
    room3_gulyabani->up = room6_hinkirmunkur;
    room3_gulyabani->left = room4_maze;
    room3_gulyabani->down = room1_start;

    room4_maze->down = room4_maze->left = NULL;
    room4_maze->right = room3_gulyabani;
    room4_maze->up = room5_storage;

    room5_storage->up = room5_storage->left = NULL;
    room5_storage->right = room6_hinkirmunkur;
    room5_storage->down = room4_maze;

    room6_hinkirmunkur->up = NULL;
    room6_hinkirmunkur->right = room7_tepegoz;
    room6_hinkirmunkur->down = room3_gulyabani;
    room6_hinkirmunkur->left = room5_storage;

    room7_tepegoz->up = room7_tepegoz->right = room7_tepegoz->down = NULL;
    room7_tepegoz->left = room6_hinkirmunkur;

    player_ptr->current_room = room1_start;

    Item *wooden_sword;
    if (initialize_item(&wooden_sword, "wooden_sword", 5, "use to attack enemies") == 0) {
        player_ptr->inventory[player_ptr->item_counter] = wooden_sword;
        player_ptr->item_counter++;
        printf("sword added");
    }

    Item *kimiz;
    if (initialize_item(&kimiz, "kimiz", 40, "bread will heal you") == 0) {
        player_ptr->inventory[player_ptr->item_counter] = kimiz;
        player_ptr->item_counter++;
    }

    Item *gold_spear;
    if (initialize_item(&gold_spear, "gold_spear", 100, "sharp, use to attack enemies") == 0) {
        room2_trap->list[room2_trap->item_counter] = gold_spear;
        room2_trap->item_counter++;
    }

    Entity *gulyabani;
    if (initialize_entity(&gulyabani, "Gulyabani", 80, 15) == 0) {
        room3_gulyabani->entity = gulyabani;
    } 
    Item *heart_poiton;
    if (initialize_item(&heart_poiton, "heart_poiton", 150, "increase your heart and heal you") == 0) {
        room3_gulyabani->list[room3_gulyabani->item_counter] = heart_poiton;
        room3_gulyabani->item_counter++;
    } 

    Item *baklava;
    if (initialize_item(&baklava, "baklava", 30, "baklava will heal you") == 0) {
        room5_storage->list[room5_storage->item_counter] = baklava;
        room5_storage->item_counter++;
    } 
    Item *delight;
    if (initialize_item(&delight, "delight", 20, "turkish_delight will heal you") == 0) {
        room5_storage->list[room5_storage->item_counter] = delight;
        room5_storage->item_counter++;
    } 
    Item *bow_arrow;
    if (initialize_item(&bow_arrow, "bow_arrow", 50, "use to attack enemies") == 0) {
        room5_storage->list[room5_storage->item_counter] = bow_arrow;
        room5_storage->item_counter++;
    }
    
    Entity *hinkir_munkur;
    if (initialize_entity(&hinkir_munkur, "Hinkir_munkur", 250, 30) == 0) {
        room6_hinkirmunkur->entity = hinkir_munkur;
    } 
    Item *poiton;
    if (initialize_item(&poiton, "poiton", 20, "increase your strength") == 0) {
        room6_hinkirmunkur->list[room6_hinkirmunkur->item_counter] = poiton;
        room6_hinkirmunkur->item_counter++;
    } 

    Entity *tepegoz;
    if (initialize_entity(&tepegoz, "tepegoz", 600, 75) == 0) {
        room7_tepegoz->entity = tepegoz;
    } 

}