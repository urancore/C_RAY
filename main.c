#include "ray.h"

void HandleMouseClick(int x, int y)
{
	int mapX = x / BLOCK_SIZE;
	int mapY = y / BLOCK_SIZE;

	if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT) {
		// map[mapY][mapX] = !map[mapY][mapX];
		if (map[mapY][mapX].type == FLOOR) {
			map[mapY][mapX].type = WALL;
		} else if (map[mapY][mapX].type == WALL) {
			map[mapY][mapX].type = FLOOR;
		}
	}
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
