#include "include/core/core_types.h"
#include "include/system/input.h"
#include "include/utils/utils.h"
#include "include/globals.h"

KeyBind key_bindings[MAX_KEY_BINDINGS];
int num_key_bindings = 0;

void bind_key(int key, void (*key_func)(), int is_continuous, int is_pressed)
{
    if (num_key_bindings < MAX_KEY_BINDINGS) {
        key_bindings[num_key_bindings].key_code = key;
        key_bindings[num_key_bindings].action = key_func;
        key_bindings[num_key_bindings].is_continuous = is_continuous;
        key_bindings[num_key_bindings].is_pressed = is_pressed;
        num_key_bindings++;
    } else {
        Sys_Error("max binds error");
    }
}


// bind funcs
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
