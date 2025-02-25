#include "ray.h"

int u_check_collision(float x, float y)
{
	int map_x = x / BLOCK_SIZE;
	int map_y = y / BLOCK_SIZE;

	if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT) {
		return 1;
	}
	if (map[map_y][map_x].type == WALL) {
		return 1;
	}
	if (map[map_y][map_x].type == TRIGGER) {
		return 0;  // переделай
	}
	return 0;
}
