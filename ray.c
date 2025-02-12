#include "ray.h"

unsigned char map[MAP_HEIGHT][MAP_WIDTH] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
	{1,1,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
	{1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

float cast_ray(float angle)
{
	float distance;

	float sin_a = sinf(angle);
	float cos_a = cosf(angle);

	float ray_x = player.pos.x + player.width / 2;
	float ray_y = player.pos.y + player.height / 2;

	float x_step = (cos_a >= 0) ? 1 : -1;
	float y_step = (sin_a >= 0) ? 1 : -1;

	float x_dist = (x_step > 0) ? ((int)(ray_x / BLOCK_SIZE + 1) * BLOCK_SIZE - ray_x) : (ray_x - (int)(ray_x / BLOCK_SIZE) * BLOCK_SIZE);
	float y_dist = (y_step > 0) ? ((int)(ray_y / BLOCK_SIZE + 1) * BLOCK_SIZE - ray_y) : (ray_y - (int)(ray_y / BLOCK_SIZE) * BLOCK_SIZE);

	float x_ray_len = (cos_a != 0) ? fabsf(x_dist / cos_a) : 1e30f;
	float y_ray_len = (sin_a != 0) ? fabsf(y_dist / sin_a) : 1e30f;

	while (1) {
		if (x_ray_len < y_ray_len) {
			ray_x += x_step * BLOCK_SIZE;
			distance = x_ray_len;
			x_ray_len += fabsf(BLOCK_SIZE / cos_a);
		} else {
			ray_y += y_step * BLOCK_SIZE;
			distance = y_ray_len;
			y_ray_len += fabsf(BLOCK_SIZE / sin_a);
		}

		int map_x = (int)ray_x / BLOCK_SIZE;
		int map_y = (int)ray_y / BLOCK_SIZE;

		if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT) {
			break;
		}

		if (map[map_y][map_x]) {
			break;
		}
	}

	return distance;
}

void R_Render(void)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	handle_keys_event();

	int view_width = WW;
	int view_height = WH;
	Rect sky = {{0, 0}, view_width, view_height / 2};
	Rect ground = {{0, view_height / 2}, view_width, view_height / 2};

	r_drawRect(&ground, DOOM_FLOOR);
	r_drawRect(&sky, DOOM_CEILING);

	for (int i = 0; i < NUM_RAYS; i++) {
		float ray_angle = player.angle - player.fov / 2 + (player.fov * i) / NUM_RAYS;
		float distance = cast_ray(ray_angle);

		distance *= cosf(ray_angle - player.angle);

		float wall_height = (BLOCK_SIZE / distance) * ((view_width / 2) / tanf(player.fov / 2));

		int wall_top = (view_height / 2) - (wall_height / 2);
		int wall_bottom = (view_height / 2) + (wall_height / 2);


		if (wall_top < 0) wall_top = 0;
		if (wall_bottom >= view_height) wall_bottom = view_height - 1;


		float shade = 1.0f - fminf(distance / 500.0f, 0.8f);
		Color wall_color = DOOM_WALL;

		wall_color.r *= shade;
		wall_color.g *= shade;
		wall_color.b *= shade;

		int x = i * view_width / NUM_RAYS;
		r_drawLine(x, wall_top, x, wall_bottom, 5.0f, wall_color);

	}

	// Draw crosshair
	int crosshair_size = 10;
	int crosshair_thickness = 2;
	int center_x = view_width / 2;
	int center_y = view_height / 2;

	// Horizontal line
	r_drawLine(center_x - crosshair_size, center_y,
		center_x + crosshair_size, center_y,
		crosshair_thickness, WHITE);

	// Vertical line
	r_drawLine(center_x, center_y - crosshair_size,
		center_x, center_y + crosshair_size,
		crosshair_thickness, WHITE);

	draw_mini_map(3, RED, BLUE);
	SwapBuffers(hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_DESTROY:
		return 0;
	case WM_ACTIVATE:
		if (LOWORD(wparam) != WA_INACTIVE) {
			// capture mouse on window activation
			SetCapture(hwnd);
			ShowCursor(FALSE);
		} else {
			ReleaseCapture();
			ShowCursor(TRUE);
		}
		break;
	default:
		return DefWindowProcA(hwnd, msg, wparam, lparam);
	}
	return 0;
}

int main()
{
	WNDCLASSA wcl;
	memset(&wcl, 0, sizeof(wcl));

	player.pos.x = 100;
	player.pos.y = 100;
	player.angle = 0;
	player.fov = PI / 2; // 90 fov
	player.height = 10;
	player.sensitivity = 0.003;
	player.speed = 0.5;
	player.width = 10;

	RECT rect;
	GetClientRect(window, &rect);
	last_mouse_x = rect.right / 2;

	wcl.lpfnWndProc = WndProc;
	wcl.lpszClassName = "CRayWindow";

	RegisterClassA(&wcl);

	window = CreateWindowExA(0, "CRayWindow", "cray_v0b.exe", WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
			0, 0, WW, WH, 0, 0, 0, 0);

	GL_Init();
	ShowWindow(window, SW_SHOWNORMAL);

	unsigned char running = 1;
	MSG msg;

	while(running) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message == WM_QUIT)
				running = 0;
			else {
				DispatchMessage(&msg);
				TranslateMessage(&msg);
			}
		} else {
			handle_mouse_movement();
			R_Render();
		}
	}

	GL_Shutdown();
	DestroyWindow(window);
	return 0;
}
