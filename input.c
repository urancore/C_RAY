#include "ray.h"
int movement_key_pressed = 0;
KeyBind key_bindings[] = {
    {0x57, 		move_forward, 	1, 0},    	// W key
    {0x53, 		move_backward, 	1, 0},   	// S key
    {0x44, 		strafe_right, 	1, 0},    	// D key
    {0x41, 		strafe_left, 	1, 0},     	// A key
	{0x45, 		clip_cursor, 	0, 0},		// E key курсор показывается через !!!!несколько (2) сек!!!! хз, ограничения winapi, может быть.
    {VK_ESCAPE, quit_game, 		0, 0}		// ESC key
};

void i_handle_keys_event(void)
{
    int key_binds_list_size = sizeof(key_bindings) / sizeof(key_bindings[0]);
    for (int i = 0; i < key_binds_list_size; i++) {
        short key_state = GetAsyncKeyState(key_bindings[i].key_code);

        if (key_state & 0x8000) {  // Key is currently pressed
            if (key_bindings[i].is_continuous || !key_bindings[i].is_pressed) {
                key_bindings[i].action();
                key_bindings[i].is_pressed = 1;

				if (key_bindings[i].action == move_forward ||
                    key_bindings[i].action == move_backward ||
                    key_bindings[i].action == strafe_right ||
                    key_bindings[i].action == strafe_left) {
                    movement_key_pressed = 1;
                }
            }
        } else {  // Key is not pressed
            key_bindings[i].is_pressed = 0;
        }
		if (!movement_key_pressed) {
			player_walk = 0;
		}
    }
}

void i_handle_mouse_movement(void)
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
	if (cursor_enabled) {
		RECT rect;
		GetClientRect(window, &rect);
		ClipCursor(&rect);
		ShowCursor(FALSE);
		int center_x = rect.right / 2;
		int center_y = rect.bottom / 2;
		POINT center = {center_x, center_y};
		ClientToScreen(window, &center);
		SetCursorPos(center.x, center.y);
		last_mouse_x = center_x;

	} else {
		ClipCursor(NULL);
		ShowCursor(TRUE);
	}
}
