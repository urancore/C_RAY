#include "ray.h"

int check_collision(float x, float y)
{
	int map_x = x / BLOCK_SIZE;
	int map_y = y / BLOCK_SIZE;

	if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT) {
		return 1;
	}

	return map[map_y][map_x] == 1;
}
