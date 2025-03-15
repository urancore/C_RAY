#ifndef RENDERER_H
#define RENDERER_H

#include "../core/core_types.h"
#include "../core/entity.h"

void set_color(Color color);
void r_drawRect(rect_t *rect, Color color);
void r_drawPoint(int x, int y, int size, Color color);
void r_drawLine(int start_x, int start_y, int end_x, int end_y, float line_size, Color color);
void r_drawCircle(int x, int y, int radius, Color color);
void r_drawMap(game_object_t map[MAP_HEIGHT][MAP_WIDTH], rect_t* mapArea);
void r_drawSky(int view_width, int view_height);
void r_drawGround(int view_width, int view_height);
void r_drawChar(int x, int y, char c);
void r_drawCrosshair(int crosshair_size, int crosshair_thickness, Color color);


#endif
