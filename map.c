#include "ray.h"

void load_map(void)
{
	FILE *file = fopen("map.map", "rb");
	if (file) {
		fread(map, sizeof(unsigned char), MAP_WIDTH * MAP_HEIGHT, file);
		fclose(file);
	}
}

void save_map(void)
{
	FILE *file = fopen("map.map", "wb");
	if (file) {
		fwrite(map, sizeof(unsigned char), MAP_WIDTH * MAP_HEIGHT, file);
		fclose(file);
	}
}

void draw_mini_map(int size, Color player_color, Color player_line)
{
		// Draw mini-map
		int map_size = WH / size;
		Rect mini_map = {{0, 0}, map_size, map_size};
		r_drawRect(&mini_map, BLACK);
		r_drawMap(map, &mini_map);

		// Draw player on mini-map
		float scale = (float)map_size / (MAP_WIDTH * BLOCK_SIZE);
		Rect mini_player;
		mini_player.pos.x = mini_map.pos.x + player.pos.x * scale;
		mini_player.pos.y = mini_map.pos.y + player.pos.y * scale;
		mini_player.width = player.width * scale;
		mini_player.height = player.height * scale;
		r_drawRect(&mini_player, player_color);

		// Draw player direction on mini-map
		float dir_length = 20.0f * scale;
		float dir_end_x = mini_player.pos.x + cosf(player.angle) * dir_length;
		float dir_end_y = mini_player.pos.y + sinf(player.angle) * dir_length;
		r_drawLine(mini_player.pos.x, mini_player.pos.y, dir_end_x, dir_end_y, 1.0f, player_line);
}
