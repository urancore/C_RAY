#include "include/core/core_types.h"
#include "include/game/map.h"
#include "include/system/key.h"
#include "include/core/bind.h"
#include "include/globals.h"

void init_player(void)
{
	player.pos.x = BLOCK_SIZE*2;
	player.pos.y = BLOCK_SIZE*2;
	player.angle = 0;
	player.fov = PI / 2; // 60 fov
	player.height = 10;
	player.sensitivity = 0.003;
	player.speed = 0.5;
	player.width = 10;
}

void init_binds(void)
{
	bind_key(K_W, 	move_forward, 	1, 0);
	bind_key(K_A, 	strafe_left, 	1, 0);
	bind_key(K_S, 	move_backward, 	1, 0);
	bind_key(K_D, 	strafe_right, 	1, 0);
	bind_key(K_E, 	strafe_right, 	1, 0);
	bind_key(K_ESC, quit_game, 		0, 0);
}

void GL_Init(void)
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	hdc = GetDC(window);
	memset(&pfd, 0, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(hdc, &pfd);

	SetPixelFormat(hdc, iFormat, &pfd);

	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);
	glOrtho(0, WW, WH, 0, -1, 1);
}

void GL_Shutdown(void)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hrc);
	ReleaseDC(window, hdc);
}
