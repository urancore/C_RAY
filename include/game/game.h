#ifndef GAME_H
#define GAME_H

#include "../core/event.h"
#include "../core/entity.h"
#include "../core/player.h"

extern game_object_t map[MAP_HEIGHT][MAP_WIDTH];
extern Player player;

void Game_Initialize(void);
void Game_Update(void);
void Game_Shutdown(void);

#endif
