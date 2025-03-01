#include "ray.h"

/*
* 0 - Fill window
* 1 - Sky/Ground
* 2 - Walls
* 3 - Hands/Weapon
* 4 - Map/Hud
* 5 - console
* 6 - text
* 7 - etc
*/

float R_CastRay(float angle)
{
	float distance;

	float sin_a = sinf(angle);
	float cos_a = cosf(angle);

	float ray_x = player.pos.x + player.width / 2;
	float ray_y = player.pos.y + player.height / 2;
    // что нужно ещё добавить? перекинуть функции по файлам и новые функции инициализировать в ray.h
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

	r_drawSky(view_width, view_height);
	r_drawGround(view_width, view_height);


	for (int i = 0; i < NUM_RAYS; i++) {

		float ray_angle = player.angle - player.fov / 2 + (player.fov * i) / NUM_RAYS;
		float distance = R_CastRay(ray_angle);

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


	m_draw_mini_map(0, 0, MAP_WIDTH*10, MAP_HEIGHT*10, RED, GREEN);
	i_handle_keys_event();
	r_drawCrosshair(6, 1, RED);
	r_sprint(WW-200, WH-100, "ESC - for quit", 15, GREEN);
	SwapBuffers(hdc);
}
