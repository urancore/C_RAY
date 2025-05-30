#ifndef HUD_H
#define HUD_H

#include "../core/core_types.h"

void r_drawHud(void);
void r_drawCrosshair(int size, int thickness, Color color);
void r_sprint(int x, int y, char *str, size_t len, Color color);

#endif
