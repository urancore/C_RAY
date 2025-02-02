#include <GL/gl.h>

#include "c_ray.h"

static void r_drawQuad(int x, int y, int width, int height, Color color)
{
    if (width <= 0 || height <= 0) return; // error

    glColor3f((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b);
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

void r_drawLine(int start_x, int start_y, int end_x, int end_y, Color color)
{
    glColor3f(color.r, color.g, color.b);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2i(start_x, start_y);
    glVertex2i(end_x, end_y);
    glEnd();
}
