#include "ray.h"
#include "system.h"

// это точно сработает? чекни sys_win и system че ты афк? скомпиль для теста
#define D_W (game_object_t){.type=WALL}
#define D_F (game_object_t){.type=FLOOR}

// самое тупое и простое решение
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

game_object_t map[MAP_HEIGHT][MAP_WIDTH] = {
	{D_W,D_W,D_W,D_W,D_W,D_W,D_W,D_W,D_W,D_W},
	{D_W,D_F,D_F,D_W,D_F,D_F,D_W,D_F,D_W,D_W},
	{D_W,D_F,D_F,D_F,D_F,D_F,D_F,D_F,D_F,D_W},
	{D_W,D_F,D_F,D_W,D_F,D_W,D_F,D_W,D_F,D_W},
	{D_W,D_F,D_F,D_F,D_F,D_W,D_F,D_W,D_F,D_W},
	{D_W,D_F,D_F,D_F,D_F,D_F,D_F,D_F,D_F,D_W},
	{D_W,D_F,D_W,D_F,D_F,D_W,D_F,D_W,D_F,D_W},
	{D_W,D_F,D_W,D_W,D_F,D_W,D_F,D_W,D_F,D_W},
	{D_W,D_F,D_F,D_F,D_F,D_F,D_F,D_F,D_F,D_W},
	{D_W,D_W,D_W,D_W,D_W,D_F,D_W,D_F,D_W,D_W},
	{D_W,D_W,D_W,D_W,D_W,D_F,D_W,D_F,D_W,D_W},
	{D_W,D_W,D_W,D_W,D_W,D_F,D_W,D_F,D_W,D_W},
	{D_W,D_F,D_F,D_F,D_W,D_F,D_W,D_F,D_W,D_W},
	{D_W,D_F,D_W,D_F,D_W,D_F,D_W,D_F,D_F,D_W},
	{D_W,D_F,D_F,D_F,D_W,D_F,D_W,D_F,D_W,D_W},
	{D_W,D_W,D_F,D_F,D_F,D_F,D_W,D_F,D_W,D_W},
	{D_W,D_F,D_F,D_F,D_W,D_F,D_F,D_F,D_F,D_W},
	{D_W,D_F,D_W,D_F,D_W,D_F,D_W,D_W,D_F,D_W},
	{D_W,D_F,D_W,D_W,D_W,D_F,D_W,D_W,D_F,D_W},
	{D_W,D_F,D_F,D_F,D_F,D_F,D_W,D_W,D_F,D_W},
	{D_W,D_W,D_F,D_F,D_F,D_F,D_F,D_F,D_F,D_W},
	{D_W,D_W,D_F,D_W,D_F,D_W,D_W,D_W,D_F,D_W},
	{D_W,D_W,D_F,D_W,D_F,D_W,D_W,D_W,D_F,D_W},
	{D_W,D_W,D_F,D_W,D_F,D_F,D_F,D_F,D_F,D_W},
	{D_W,D_W,D_F,D_W,D_F,D_W,D_W,D_W,D_F,D_W},
	{D_W,D_F,D_F,D_W,D_F,D_W,D_W,D_W,D_F,D_W},
	{D_W,D_F,D_F,D_W,D_F,D_F,D_F,D_F,D_F,D_W},
	{D_W,D_F,D_F,D_F,D_F,D_W,D_W,D_W,D_W,D_W},
	{D_W,D_F,D_W,D_F,D_F,D_F,D_F,D_F,D_F,D_W},
	{D_W,D_W,D_W,D_W,D_W,D_W,D_W,D_W,D_W,D_W},
};

// TODO: перенести в sys_win.c и sys_linux.c
int main()
{
	Game_Initialize();

	unsigned char running = 1;
    while(running) {
        if (!window_process_messages()) {
            running = 0;
        } else {
			Game_Update();
        }
    }

	Game_Shutdown();
	window_destroy();
	return 0;
}
