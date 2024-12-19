#ifndef ENTITY_H
#define ENTITY_H

#define NAME_LENGTH 30

typedef struct Entity {
    char name[NAME_LENGTH];
    int health;
    int damage;
} Entity;

int initialize_entity(Entity **entity_ptr, const char *name, int health, int damage);
void get_entity_info(Entity *entity);

#endif