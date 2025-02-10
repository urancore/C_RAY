#include "ray.h"


void move_forward(void)
{
    move_player(player.angle);
}

void move_backward(void)
{
    move_player(player.angle + PI);
}

void strafe_right(void)
{
    move_player(player.angle + PI/2);
}

void strafe_left(void)
{
    move_player(player.angle - PI/2);
}

void rotate_left(void)
{
    player.angle -= 0.1;
    if (player.angle < 0) player.angle += 2 * PI;
}

void rotate_right(void)
{
    player.angle += 0.1;
    if (player.angle >= 2 * PI) player.angle -= 2 * PI;
}

void quit_game(void)
{
    PostQuitMessage(0);
}


KeyBind key_bindings[] = {
    {0x57, 		move_forward, 	1},    	// W key
    {0x53, 		move_backward, 	1},   	// S key
    {0x44, 		strafe_right, 	1},    	// D key
    {0x41, 		strafe_left, 	1},     // A key
    {0x51, 		rotate_left, 	1},     // Q key
    {0x45, 		rotate_right, 	1},    	// E key
    {VK_ESCAPE, quit_game, 		1}		// ESC key
};
