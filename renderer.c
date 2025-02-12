#include "ray.h"

static void r_drawQuad(int x, int y, int width, int height, Color color)
{
	if (width <= 0 || height <= 0) return; // error

	glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.alpha);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + width, y);
	glVertex2i(x + width, y + height);
	glVertex2i(x, y + height);
	glEnd();
}

void r_drawRect(Rect *rect, Color color)
{
	r_drawQuad(rect->pos.x, rect->pos.y,
			rect->width, rect->height,
			color);
}

void r_drawPoint(int x, int y, int size, Color color)
{
	r_drawQuad(x, y,
			size, size,
			color);
}

void r_drawLine(int start_x, int start_y, int end_x, int end_y, float line_size, Color color)
{
	glColor3f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b);
	glLineWidth(line_size);

	glBegin(GL_LINES);
	glVertex2i(start_x, start_y);
	glVertex2i(end_x, end_y);
	glEnd();
}

void r_drawMap(unsigned char map[MAP_HEIGHT][MAP_WIDTH], Rect* mapArea)
{
	Color color;
	float scale_x = (float)mapArea->width / (MAP_WIDTH * BLOCK_SIZE);
	float scale_y = (float)mapArea->height / (MAP_HEIGHT * BLOCK_SIZE);
	float scale = (scale_x < scale_y) ? scale_x : scale_y;  // Use the smaller scale to fit the map

	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			if (map[y][x] == 0) {
				color.r = 0.0f;
				color.g = 0.0f;
				color.b = 0.0f;
			} else {
				color.r = 1.0f;
				color.g = 1.0f;
				color.b = 1.0f;
			}

			float block_size = BLOCK_SIZE * scale;
			float draw_x = mapArea->pos.x + x * block_size;
			float draw_y = mapArea->pos.y + y * block_size;

			r_drawPoint(draw_x, draw_y, block_size, color);
		}
	}
}


void flashbang(float flash_duration) // test_1234
{
	(void)flash_duration;

	Rect rect;
	rect.pos.x = 0;
	rect.pos.y = 0;
	rect.width = WW;
	rect.height = WH;

	Color color;
	color.r = 1.0f;
	color.g = 1.0f;
	color.b = 1.0f;
	color.alpha = flash_duration;
	r_drawRect(&rect, color);
}
