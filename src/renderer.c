#include "include/core/core_types.h"
#include "include/globals.h"
#include "include/core/entity.h"
#include "include/utils/utils.h"


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

void r_drawRect(rect_t *rect, Color color)
{
	r_drawQuad(rect->pos.x, rect->pos.y,
			rect->width, rect->height,
			color);
}

void r_drawCircle(int x, int y, int radius, Color color)
{
    const int num_segments = 64;
    const float theta = 2.0f * PI / (float)num_segments;
    const float c = cosf(theta);
    const float s = sinf(theta);
    float t;

    float x_pos = (float)radius;
    float y_pos = 0;

    set_color(color);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)
    {
        glVertex2f(x_pos + x, y_pos + y);

        t = x_pos;
        x_pos = c * x_pos - s * y_pos;
        y_pos = s * t + c * y_pos;
    }
    glEnd();
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
				color = BLACK;
				break;
			case WALL:
				color = WHITE;
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

            float draw_x = mapArea->pos.x + map_x * scale;
            float draw_y = mapArea->pos.y + map_y * scale;

            r_drawPoint(draw_x, draw_y, scale, color);
        }
    }
}

void r_drawChar(int x, int y, char c)
{
	glRasterPos2i(x, y);
	glPushAttrib(GL_LIST_BIT);
	glListBase(fontOffset);
	glCallLists(1, GL_UNSIGNED_BYTE, &c);
	glPopAttrib();
}


// ========= custom =========
void r_drawSky(int view_width, int view_height)
{
	rect_t sky = {{0, 0}, view_width, view_height / 2};

	r_drawRect(&sky, C_RAY_CEILING);
}

void r_drawGround(int view_width, int view_height)
{
	rect_t ground = {{0, view_height / 2}, view_width, view_height / 2};
	r_drawRect(&ground, C_RAY_FLOOR);
}

void r_drawCrosshair(int crosshair_size, int crosshair_thickness, Color color)
{
	// Draw crosshair
	int center_x = view_width / 2;
	int center_y = view_height / 2;

	// Horizontal line
	r_drawLine(center_x - crosshair_size, center_y,
		center_x + crosshair_size, center_y,
		crosshair_thickness, color);

	// Vertical line
	r_drawLine(center_x, center_y - crosshair_size,
		center_x, center_y + crosshair_size,
		crosshair_thickness, color);
}
