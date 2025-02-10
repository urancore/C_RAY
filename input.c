#include "ray.h"

void check_keys(void)
{
	if (GetAsyncKeyState(0x57) & 0x8000) { // W key (forward)
		move_player(player.angle);
	}
	if (GetAsyncKeyState(0x53) & 0x8000) { // S key (backward)
		move_player(player.angle + PI);
	}
	if (GetAsyncKeyState(0x44) & 0x8000) { // D key (strafe right)
		move_player(player.angle + PI/2);
	}
	if (GetAsyncKeyState(0x41) & 0x8000) { // A key (strafe left)
		move_player(player.angle - PI/2);
	}
	if (GetAsyncKeyState(0x51) & 0x8000) { // Q key (rotate left)
		player.angle -= 0.1;
		if (player.angle < 0) player.angle += 2 * PI;
	}
	if (GetAsyncKeyState(0x45) & 0x8000) { // E key (rotate right)
		player.angle += 0.1;
		if (player.angle >= 2 * PI) player.angle -= 2 * PI;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
		PostQuitMessage(0);
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
