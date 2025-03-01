#include "ray.h"

void init_player()
{
	player.pos.x = BLOCK_SIZE*2;
	player.pos.y = BLOCK_SIZE*2;
	player.angle = 0;
	player.fov = PI / 2; // 60 fov
	player.height = 10;
	player.sensitivity = 0.003;
	player.speed = 0.1;
	player.width = 10;
}
