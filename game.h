#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "room.h"
#include "item.h"
#include "entity.h"

// my global variables
extern Player player;
extern Player *player_ptr;
extern Room *room1_start, *room2_trap, *room3_gulyabani, *room4_maze;
extern Room *room5_storage, *room6_hinkirmunkur, *room7_tepegoz;
extern Item *key;

void list_saves();
void save_game(const char *filepath);
void load_game(const char *filepath);
void room4();
int random_damage(int min);
void get_map();
void get_command_descriptions();
void in_game_commands_loop();
void default_values();

#endif