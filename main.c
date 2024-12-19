#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main() {
    srand(time(NULL));
    default_values();

    in_game_commands_loop();

    return 0;
}