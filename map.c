#include "include/core/core_types.h"
#include "include/core/player.h"
#include "include/game/map.h"
#include "include/rendering/renderer.h"
#include "include/globals.h"

void m_load_map(void)
{
	FILE *file = fopen("map.map", "rb");
	if (file) {
		fread(map, sizeof(unsigned char), MAP_WIDTH * MAP_HEIGHT, file);
		fclose(file);
	}
}

void m_save_map(void)
{
	FILE *file = fopen("map.map", "wb");
	if (file) {
		fwrite(map, sizeof(unsigned char), MAP_WIDTH * MAP_HEIGHT, file);
		fclose(file);
	}
}

void m_draw_mini_map(int x, int y, int map_width, int map_height, Color player_color, Color player_line)
{
    // Calculate scale
    float scale_x = (float)map_width / (MAP_WIDTH * BLOCK_SIZE);
    float scale_y = (float)map_height / (MAP_HEIGHT * BLOCK_SIZE);
    float scale = (scale_x < scale_y) ? scale_x : scale_y;  // Use the smaller scale to fit the map

    // Draw mini-map
    rect_t mini_map = {{x, y}, map_width, map_height};
    r_drawRect(&mini_map, BLACK);
    r_drawMap(map, &mini_map);

    // Draw player on mini-map
    float player_x = mini_map.pos.x + (player.pos.x / BLOCK_SIZE) * (map_width / MAP_WIDTH);
    float player_y = mini_map.pos.y + (player.pos.y / BLOCK_SIZE) * (map_height / MAP_HEIGHT);
    float player_size = 10.0f * scale;  // Adjust this value for desired player size on mini-map

    r_drawPoint(player_x, player_y, player_size, player_color);

    // Draw player direction on mini-map
    float dir_length = 10.0f * scale;
    float dir_end_x = player_x + cosf(player.angle) * dir_length;
    float dir_end_y = player_y + sinf(player.angle) * dir_length;
    r_drawLine(player_x, player_y, dir_end_x, dir_end_y, 1.0f, player_line);
}
