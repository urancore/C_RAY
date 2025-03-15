#ifndef PLAYER_H
#define PLAYER_H

#include "core_types.h"

typedef struct {
    Position pos;
    float angle, fov;
    float sensitivity, speed;
    float width, height;
} Player;


extern unsigned short player_walk;
extern Player player;


#endif
