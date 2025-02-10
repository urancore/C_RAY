#include "ray.h"

// global vars externed in ray.h
// keep in sync
HWND window = 0;
HDC hdc = 0;
HGLRC hrc = 0;

int last_mouse_x = 0;
Player player = {0};
