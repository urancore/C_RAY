#include "ray.h"


void move_forward(void)
{
    u_move_player(player.angle);
	player_walk = 1;
	// cmd_append_buffer("move forward\n", GREEN);
}

void move_backward(void)
{
    u_move_player(player.angle + PI);
	player_walk = 1;
	// cmd_append_buffer("move backward\n", RED);
}

void strafe_right(void)
{
    u_move_player(player.angle + PI/2);
	player_walk = 1;
	// cmd_append_buffer("strafe right\n", YELLOW);
}

void strafe_left(void)
{
    u_move_player(player.angle - PI/2);
	player_walk = 1;
	// cmd_append_buffer("strafe left\n", BLUE);
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

void clip_cursor(void)
{
	cursor_enabled = !cursor_enabled;
}

void quit_game(void)
{
    PostQuitMessage(0);
}
