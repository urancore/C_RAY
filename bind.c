#include "ray.h"


void move_forward(void)
{
    u_move_player(player.angle);
}

void move_backward(void)
{
    u_move_player(player.angle + PI);
}

void strafe_right(void)
{
    u_move_player(player.angle + PI/2);
}

void strafe_left(void)
{
    u_move_player(player.angle - PI/2);
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

void test_btn(void)
{
	e_flashbang_duration = 1.0f;
}

void quit_game(void)
{
    PostQuitMessage(0);
}
