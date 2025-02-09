#include "ray.h"

#define NUM_RAYS 264

float player_angle = 0.0f;
float fov = PI / 2.0f; // 60 degrees field of view
int last_mouse_x = 0;
float sensitivity = 0.003f;
Rect player;

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

void handle_mouse_movement()
{
	POINT mouse_pos;
	GetCursorPos(&mouse_pos);
	ScreenToClient(window, &mouse_pos);

	int delta_x = mouse_pos.x - last_mouse_x;
	player_angle += (float)delta_x * sensitivity;

	// Нормализация угла
	while (player_angle < 0) player_angle += 2 * PI;
	while (player_angle >= 2 * PI) player_angle -= 2 * PI;

	last_mouse_x = mouse_pos.x;

	// Возвращаем курсор в центр окна
	RECT rect;
	GetClientRect(window, &rect);
	int center_x = rect.right / 2;
	int center_y = rect.bottom / 2;
	POINT center = {center_x, center_y};
	ClientToScreen(window, &center);
	SetCursorPos(center.x, center.y);
	last_mouse_x = center_x;
}

void init_player()
{
	player.pos.x = 100;
	player.pos.y = 100;
	player.width = 10;
	player.height = 10;
}
void cast_ray(float angle, float *distance, int *map_x, int *map_y)
{
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
            *distance = x_ray_len;
            x_ray_len += fabsf(BLOCK_SIZE / cos_a);
        } else {
            ray_y += y_step * BLOCK_SIZE;
            *distance = y_ray_len;
            y_ray_len += fabsf(BLOCK_SIZE / sin_a);
        }

        *map_x = (int)ray_x / BLOCK_SIZE;
        *map_y = (int)ray_y / BLOCK_SIZE;

        if (*map_x < 0 || *map_x >= MAP_WIDTH || *map_y < 0 || *map_y >= MAP_HEIGHT) {
            break;
        }

        if (map[*map_y][*map_x] == 1) {
            break;
        }
    }
}

void move_player(Rect *player, float angle, float speed)
{
	float dx = cosf(angle) * speed;
	float dy = sinf(angle) * speed;

	int new_x = player->pos.x + (int)dx;
	int new_y = player->pos.y + (int)dy;

	// Проверка коллизий для всех углов игрока
	if (!check_collision(new_x, new_y) &&
			!check_collision(new_x + player->width - 1, new_y) &&
			!check_collision(new_x, new_y + player->height - 1) &&
			!check_collision(new_x + player->width - 1, new_y + player->height - 1))
	{
		player->pos.x = new_x;
		player->pos.y = new_y;
	}
}

void check_keys()
{
	float speed = 2.0f;

	if (GetAsyncKeyState(0x57) & 0x8000) { // W key (forward)
		move_player(&player, player_angle, speed);
	}
	if (GetAsyncKeyState(0x53) & 0x8000) { // S key (backward)
		move_player(&player, player_angle + PI, speed);
	}
	if (GetAsyncKeyState(0x44) & 0x8000) { // D key (strafe right)
		move_player(&player, player_angle + PI/2, speed);
	}
	if (GetAsyncKeyState(0x41) & 0x8000) { // A key (strafe left)
		move_player(&player, player_angle - PI/2, speed);
	}
	if (GetAsyncKeyState(0x51) & 0x8000) { // Q key (rotate left)
		player_angle -= 0.1f;
		if (player_angle < 0) player_angle += 2 * PI;
	}
	if (GetAsyncKeyState(0x45) & 0x8000) { // E key (rotate right)
		player_angle += 0.1f;
		if (player_angle >= 2 * PI) player_angle -= 2 * PI;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
		PostQuitMessage(0);
	}
	Sleep(10);
}

void R_Render(void)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	check_keys();

	int view_width = WW;
	int view_height = WH;
	Rect sky = {{0, 0}, view_width, view_height / 2};
	Rect ground = {{0, view_height / 2}, view_width, view_height / 2};

	r_drawRect(&ground, DOOM_FLOOR);
	r_drawRect(&sky, DOOM_CEILING);

    for (int i = 0; i < NUM_RAYS; i++)
    {
        float ray_angle = player_angle - fov / 2 + (fov * i) / NUM_RAYS;
        float distance;
        int map_x, map_y;
        cast_ray(ray_angle, &distance, &map_x, &map_y);


        distance *= cosf(ray_angle - player_angle);

        float wall_height = (BLOCK_SIZE / distance) * ((view_width / 2) / tanf(fov / 2));

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



	// Draw mini-map
	int map_size = WH / 3;  // Set the size of the mini-map
	Rect mini_map = {{0, 0}, map_size, map_size};
	r_drawRect(&mini_map, BLACK);
	r_drawMap(map, &mini_map);

	// Draw player on mini-map
	float scale = (float)map_size / (MAP_WIDTH * BLOCK_SIZE);
	Rect mini_player = {
		{mini_map.pos.x + player.pos.x * scale, mini_map.pos.y + player.pos.y * scale},
		player.width * scale,
		player.height * scale
	};
	r_drawRect(&mini_player, RED);

	// Draw player direction on mini-map
	float dir_length = 20.0f * scale;
	float dir_end_x = mini_player.pos.x + cosf(player_angle) * dir_length;
	float dir_end_y = mini_player.pos.y + sinf(player_angle) * dir_length;
	r_drawLine(mini_player.pos.x, mini_player.pos.y, dir_end_x, dir_end_y, 2.0f, GREEN);
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
		if (LOWORD(wparam) != WA_INACTIVE)
		{
			// Захват мыши при активации окна
			SetCapture(hwnd);
			ShowCursor(FALSE);
		}
		else
		{
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
	WNDCLASSA    wcl;
	memset(&wcl, 0, sizeof(wcl));
	init_player();

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
