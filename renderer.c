#include "ray.h"

static void r_drawQuad(int x, int y, int width, int height, Color color)
{
	if (width <= 0 || height <= 0) return; // error

	glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.alpha);
	glBegin(GL_QUADS);
	glVertex2i((GLint)x, (GLint)y);
	glVertex2i((GLint)x + (GLint)width, (GLint)y);
	glVertex2i((GLint)x + (GLint)width, (GLint)y + (GLint)height);
	glVertex2i((GLint)x, (GLint)y + (GLint)height);
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

void r_drawMap(GameObject map[MAP_HEIGHT][MAP_WIDTH], Rect* mapArea)
{
    Color color;
    float scale_x = (float)mapArea->width / MAP_WIDTH;
    float scale_y = (float)mapArea->height / MAP_HEIGHT;
    float scale = (scale_x < scale_y) ? scale_x : scale_y;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
			switch (map[y][x].type) {
			case FLOOR:
				color = C_RAY_FLOOR;
				break;
			case WALL:
				color = C_RAY_WALL;
				break;
			case TRIGGER:
				color = YELLOW;
				break;
			case DOOR:
				color = GRAY;
				break;
			default:
				color = PURPLE;
				break;
			}
            // if (map[y][x].type == FLOOR) {
            //     color.r = 0.2f;  // Темно-серый для пола
            //     color.g = 0.2f;
            //     color.b = 0.2f;
            // } else if  {
            //     color.r = 0.5f;  // Фиолетовый для стен
            //     color.g = 0.8f;
            //     color.b = 0.5f;
            // }

            float draw_x = mapArea->pos.x + x * scale;
            float draw_y = mapArea->pos.y + y * scale;

            r_drawPoint(draw_x, draw_y, scale, color);
        }
    }
}

void r_drawSky(int view_width, int view_height)
{
	Rect sky = {{0, 0}, view_width, view_height / 2};

	r_drawRect(&sky, C_RAY_CEILING);
}

void r_drawGround(int view_width, int view_height)
{
	Rect ground = {{0, view_height / 2}, view_width, view_height / 2};
	r_drawRect(&ground, C_RAY_FLOOR);
}


void e_flashbang(float flash_duration) // test_1234
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
