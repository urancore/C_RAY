#include "include/renderer_types.h"
#include "include/map.h"


// renderer.c
void r_drawRect(Rect *rect, Color color);
void r_drawPoint(int x, int y, int size, Color color);
void r_drawLine(int start_x, int start_y, int end_x, int end_y, float line_size, Color color);
void r_drawMap(unsigned char map[MAP_HEIGHT][MAP_WIDTH], Rect* mapArea);

//map.c
// void load_map(unsigned char map_data[MAP_HEIGHT][MAP_WIDTH]);

// misc.c
int check_collision(int x, int y);

