#include "ray.h"


void set_color(Color color)
{
	glColor4f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.alpha);
}


static void r_drawQuad(int x, int y, int width, int height, Color color)
{
	if (width <= 0 || height <= 0) return; // error

	set_color(color);

	glBegin(GL_QUADS);
	glVertex2i((GLint)x, (GLint)y);
	glVertex2i((GLint)x + (GLint)width, (GLint)y);
	glVertex2i((GLint)x + (GLint)width, (GLint)y + (GLint)height);
	glVertex2i((GLint)x, (GLint)y + (GLint)height);
	glEnd();
}

void r_drawrect_t(rect_t *rect, Color color)
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

void r_drawMap(game_object_t map[MAP_HEIGHT][MAP_WIDTH], rect_t* mapArea)
{
    Color color;
    float scale_x = (float)mapArea->width / MAP_WIDTH;
    float scale_y = (float)mapArea->height / MAP_HEIGHT;
    float scale = (scale_x < scale_y) ? scale_x : scale_y;

    for (int map_y = 0; map_y < MAP_HEIGHT; map_y++) {
        for (int map_x = 0; map_x < MAP_WIDTH; map_x++) {
			switch (map[map_y][map_x].type) {
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

            float draw_x = mapArea->pos.x + map_x * scale;
            float draw_y = mapArea->pos.y + map_y * scale;

            r_drawPoint(draw_x, draw_y, scale, color);
        }
    }
}

void r_drawSky(int view_width, int view_height)
{
	rect_t sky = {{0, 0}, view_width, view_height / 2};

	r_drawrect_t(&sky, C_RAY_CEILING);
}

void r_drawGround(int view_width, int view_height)
{
	rect_t ground = {{0, view_height / 2}, view_width, view_height / 2};
	r_drawrect_t(&ground, C_RAY_FLOOR);
}

void r_drawChar(int x, int y, char c)
{
	glRasterPos2i(x, y);
	glPushAttrib(GL_LIST_BIT);
	glListBase(fontOffset);
	glCallLists(1, GL_UNSIGNED_BYTE, &c);
	glPopAttrib();
}
