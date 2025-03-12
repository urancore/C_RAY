#include "ray.h"
int movement_key_pressed = 0;

void i_handle_key_event(event_t event)
{
    for (int i = 0; i < num_key_bindings; i++) {
        if (key_bindings[i].key_code == event.key) {
            if (event.type == ev_keydown) {
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
            } else if (event.type == ev_keyup) {
                key_bindings[i].is_pressed = 0;
                if (key_bindings[i].action == move_forward ||
                    key_bindings[i].action == move_backward ||
                    key_bindings[i].action == strafe_right ||
                    key_bindings[i].action == strafe_left) {
                    movement_key_pressed = 0;
                }
            }
        }
    }
}

void i_handle_mouse_event(event_t event)
{
    int delta_x = event.x;
    player.angle += (float)delta_x * player.sensitivity;

    // normalise angle
    while (player.angle < 0) player.angle += 2 * PI;
    while (player.angle >= 2 * PI) player.angle -= 2 * PI;

	last_mouse_x = event.x;

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
