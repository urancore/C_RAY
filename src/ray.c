#include "include/core/core_types.h"
#include "include/core/entity.h"
#include "include/game/game.h"
#include "include/system/win_system.h"

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
