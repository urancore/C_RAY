#include "ray.h"

KeyBind key_bindings[] = {
    {0x57, 		move_forward, 	1},    	// W key
    {0x53, 		move_backward, 	1},   	// S key
    {0x44, 		strafe_right, 	1},    	// D key
    {0x41, 		strafe_left, 	1},     // A key
    {0x51, 		rotate_left, 	1},     // Q key
    {0x45, 		rotate_right, 	1},    	// E key
    {VK_ESCAPE, quit_game, 		0}		// ESC key
};


void handle_keys_event(void)
{
	int key_binds_list_size = sizeof(key_bindings) / sizeof(key_bindings[0]);
	for (int i = 0; i < key_binds_list_size; i++) {
		if (GetAsyncKeyState(key_bindings[i].key_code) & 0x8000) {
			key_bindings[i].action();
		}
	}
}

void handle_mouse_movement(void)
{
	POINT mouse_pos;
	GetCursorPos(&mouse_pos);
	ScreenToClient(window, &mouse_pos);

	int delta_x = mouse_pos.x - last_mouse_x;
	player.angle += (float)delta_x * player.sensitivity;

	// normalise angle
	while (player.angle < 0) player.angle += 2 * PI;
	while (player.angle >= 2 * PI) player.angle -= 2 * PI;

	last_mouse_x = mouse_pos.x;

	// return cursor to center of the window
	RECT rect;
	GetClientRect(window, &rect);
	int center_x = rect.right / 2;
	int center_y = rect.bottom / 2;
	POINT center = {center_x, center_y};
	ClientToScreen(window, &center);
	SetCursorPos(center.x, center.y);
	last_mouse_x = center_x;
}

void move_player(float angle)
{
	float dx = cosf(angle) * player.speed;
	float dy = sinf(angle) * player.speed;

	float new_x = player.pos.x + dx;
	float new_y = player.pos.y + dy;

	// check collision for all player corners
	if (!check_collision(new_x, new_y) &&
		!check_collision(new_x + player.width - 1, new_y) &&
		!check_collision(new_x, new_y + player.height - 1) &&
		!check_collision(new_x + player.width - 1, new_y + player.height - 1)) {
		player.pos.x = new_x;
		player.pos.y = new_y;
	}
}
