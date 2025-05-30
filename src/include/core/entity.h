#ifndef ENTITY_H
#define ENTITY_H

#include "core_types.h"

typedef enum { WALL, FLOOR, DOOR, TRIGGER } entity_type_t;

typedef struct {
    char is_locked;
    int  key_id;
} DoorData;

typedef struct {
    int target_entity;
    void (*callback)();
} TriggerData;

typedef struct {
    entity_type_t type;
    union {
        DoorData door_data;
        TriggerData trigger_data;
    };
} game_object_t;

#endif
