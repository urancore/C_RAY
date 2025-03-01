#include "ray.h"

void Game_Initialize(void)
{
	window_initialize("Cray-v1.exe");
	GL_Init();

	init_player();
	init_font();

	window_show();

	//mouse потом сделать функцию отдельную
	RECT rect;
	GetClientRect(window, &rect);
	last_mouse_x = rect.right / 2;
}

void Game_Update(void)
{
    i_handle_mouse_movement();
	R_Render();
}

void Game_Shutdown(void)
{
	GL_Shutdown();
}
