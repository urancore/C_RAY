#include "ray.h"

// global vars externed in ray.h
// keep in sync
HWND window = 0;
HDC hdc = 0;
HGLRC hrc = 0;

float player_angle = 0;
float fov = PI / 2; // 60 degrees field of view
int last_mouse_x = 0;
float sensitivity = 0.003;
Rect player = {0};
