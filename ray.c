#include "ray.h"
#include "system.h"
// DEFINES_type (Wall, Floor)
#define D_W (game_object_t){.type=WALL}
#define D_F (game_object_t){.type=FLOOR}
// #define D_T (game_object_t){.type=TRIGGER, .trigger_data= {.target_entity}}
// #define D_D (game_object_t){.type=DOOR, .door_data= {.is_locked = 0, .key_id = 0}}

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

		if (map[map_y][map_x].type == WALL) {
			break;
		}
	}

	return distance;
}

void R_Render(void)
{
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	int view_width = WW;
	int view_height = WH;

	r_drawSky(view_width, view_height);
	r_drawGround(view_width, view_height);


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
		Color wall_color = C_RAY_WALL;

		wall_color.r *= shade;
		wall_color.g *= shade;
		wall_color.b *= shade;

		int x = i * view_width / NUM_RAYS;
		r_drawLine(x, wall_top, x, wall_bottom, 1.0f, wall_color);

	}

	// Draw crosshair
	int crosshair_size = 6;
	int crosshair_thickness = 1;
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

	m_draw_mini_map(0, 0, MAP_WIDTH*10, MAP_HEIGHT*10, RED, GREEN);
	i_handle_keys_event();
	// update_game();
	// cmd_print_buffer();
	r_sprint(WW-200, WH-100, "ESC - for quit", 15, GREEN);
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
	default:
		return DefWindowProcA(hwnd, msg, wparam, lparam);
	}
	return 0;
}

void init_player()
{
	player.pos.x = BLOCK_SIZE*2;
	player.pos.y = BLOCK_SIZE*2;
	player.angle = 0;
	player.fov = PI / 2; // 60 fov
	player.height = 10;
	player.sensitivity = 0.003;
	player.speed = 0.1;
	player.width = 10;
}

int main()
{
	WNDCLASSA wcl;
	memset(&wcl, 0, sizeof(wcl));

	wcl.lpfnWndProc = WndProc;
	wcl.lpszClassName = "CRayWindow";
	RegisterClassA(&wcl);
	window = CreateWindowExA(0, "CRayWindow", "cray_v0b.exe", WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
			0, 0, WW, WH, 0, 0, 0, 0);

	GL_Init();
	ShowWindow(window, SW_SHOWNORMAL);

	unsigned char running = 1;
	MSG msg;

	init_player();
	init_font();

	RECT rect;
	GetClientRect(window, &rect);
	last_mouse_x = rect.right / 2;

	while(running) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message == WM_QUIT) {
				running = 0;
			} else {
				DispatchMessage(&msg);
				TranslateMessage(&msg);
			}
		} else {
			i_handle_mouse_movement();
			R_Render();
		}
	}
	sys_message_box('i', "U game over");
	GL_Shutdown();
	DestroyWindow(window);
	return 0;
}
