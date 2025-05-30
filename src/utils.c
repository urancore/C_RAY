#include "include/core/core_types.h"
#include "include/game/game.h"

void set_color(Color color)
{
	glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.alpha);
}

int u_check_collision(float x, float y)
{
	int map_x = x / BLOCK_SIZE;
	int map_y = y / BLOCK_SIZE;

	if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT) {
		return 1;
	}
	if (map[map_y][map_x].type == WALL) {
		return 1;
	}
	if (map[map_y][map_x].type == TRIGGER) {
		return 0;  // переделай
	}
	if (map[map_y][map_x].type == FLOOR) {
		return 0;  // переделай
	}
	return 0;
}


void u_move_player(float angle)
{
    float dx = cosf(angle) * player.speed;
    float dy = sinf(angle) * player.speed;

    // Пробуем переместиться по горизонтали (это на 2d поверхности, не забываем)
    float new_x = player.pos.x + dx;
    char collision_x =
        u_check_collision(new_x, player.pos.y) ||
        u_check_collision(new_x + player.width - 1, player.pos.y) ||
        u_check_collision(new_x, player.pos.y + player.height - 1) ||
        u_check_collision(new_x + player.width - 1, player.pos.y + player.height - 1);

    if (!collision_x) {
        player.pos.x = new_x;
    }

    // Пробуем переместиться по вертикали (это на 2d поверхности, не забываем)
    float new_y = player.pos.y + dy;
    char collision_y =
        u_check_collision(player.pos.x, new_y) ||
        u_check_collision(player.pos.x + player.width - 1, new_y) ||
        u_check_collision(player.pos.x, new_y + player.height - 1) ||
        u_check_collision(player.pos.x + player.width - 1, new_y + player.height - 1);

    if (!collision_y) {
        player.pos.y = new_y;
    }
}
