#include "ray.h"

void process_event(event_t event)
{
    switch (event.type) {
        case ev_keydown:
        case ev_keyup:
			i_handle_key_event(event);
            break;
        case ev_mouse:
			i_handle_mouse_event(event);
            break;
    }
}
void get_events(event_t *events_buffer)
{
    // Handle keyboard events
    for (int i = 0; i < 256; i++) {
        short key_state = GetAsyncKeyState(i);
        if (key_state & 0x8000) {  // Key is pressed
            events_buffer[C_RAY_KEYBOARD_EVENT].type = ev_keydown;
            events_buffer[C_RAY_KEYBOARD_EVENT].key = i;
            break;  // Only capture the first pressed key
        } else if (key_state & 0x0001) {  // Key was released
            events_buffer[C_RAY_KEYBOARD_EVENT].type = ev_keyup;
            events_buffer[C_RAY_KEYBOARD_EVENT].key = i;
            break;  // Only capture the first released key
        }
    }

    // Handle mouse events
    POINT mouse_pos;
    GetCursorPos(&mouse_pos);
    ScreenToClient(window, &mouse_pos);

    int delta_x = mouse_pos.x - last_mouse_x;
    if (delta_x != 0) {
        events_buffer[C_RAY_MOUSE_EVENT].type = ev_mouse;
        events_buffer[C_RAY_MOUSE_EVENT].x = delta_x;
    }
}
