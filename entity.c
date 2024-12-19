#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "entity.h"

int initialize_entity(Entity **entity_ptr, const char *name, int health, int damage) {
    *entity_ptr = (Entity *)malloc(sizeof(Entity));
    if (*entity_ptr == NULL) {
        printf("Failed to allocate memory for the entity.\n");
        return -1;
    }

    strncpy((*entity_ptr)->name, name, sizeof((*entity_ptr)->name) - 1);
    (*entity_ptr)->name[sizeof((*entity_ptr)->name) - 1] = '\0';
    (*entity_ptr)->health = health;
    (*entity_ptr)->damage = damage;

    return 0;
}

void get_entity_info(Entity *entity) {
    printf("Entity: %s (health: %d, damage: %d)\n", 
            entity->name, entity->health, entity->damage);
}