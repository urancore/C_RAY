#include "ray.h"
#include "keys.h"

void init_player()
{
	player.pos.x = BLOCK_SIZE*2;
	player.pos.y = BLOCK_SIZE*2;
	player.angle = 0;
	player.fov = PI / 2; // 60 fov
	player.height = 10;
	player.sensitivity = 0.003;
	player.speed = 0.5;
	player.width = 10;
}

void init_binds()
{
	bind_key(K_W, 	move_forward, 	1, 0);
	bind_key(K_A, 	strafe_left, 	1, 0);
	bind_key(K_S, 	move_backward, 	1, 0);
	bind_key(K_D, 	strafe_right, 	1, 0);
	bind_key(K_E, 	strafe_right, 	1, 0);
	bind_key(K_ESC, quit_game, 		0, 0);
}
