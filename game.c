#include "ray.h"


void Game_Initialize(void)
{
	window_initialize("Cray-v1.exe");
	GL_Init();

	init_player();
	init_font();
	init_binds();

	window_show();

	//mouse потом сделать функцию отдельную
	RECT rect;
	GetClientRect(window, &rect);
	last_mouse_x = rect.right / 2;
}

void Game_Update(void)
{
	// events
	event_t events[2];
	get_events(events);
	process_event(events[C_RAY_KEYBOARD_EVENT]);
	process_event(events[C_RAY_MOUSE_EVENT]);

	R_Render();
}

void Game_Shutdown(void)
{
	GL_Shutdown();
}
