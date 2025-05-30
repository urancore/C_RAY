#ifndef MAP_H
#define MAP_H


#include "../core/core_types.h"
#include "../core/entity.h"

void m_load_map(void);
void m_save_map(void);
void m_draw_mini_map(int x, int y, int w, int h, Color player_color, Color player_line);

#endif
