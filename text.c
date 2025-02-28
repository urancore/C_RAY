#include "ray.h"
#include "text.h"


#define char_size_x 10
#define char_size_y 16

void init_font(void)
{
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	fontOffset = glGenLists(128);

	for (int i = 32; i < 127; i++) {
		glNewList(i + fontOffset, GL_COMPILE);
		glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, hz_text_font[i - 32]);
		glEndList();
	}
}

// добавь потом чекание размера окна и кол-ва символов
void r_sprint(int x, int y, char *str, size_t len_str, Color color)
{
	int new_x = x;
	int new_y = y;

	if (str == NULL) return;

	set_color(color);
	for (size_t i = 0; i < len_str; i++) {
		if (str[i] == '\0') {
			return;
		} else if (str[i] == '\n') {
			new_x = x;
			new_y += char_size_y;
		} else {
			r_drawChar(new_x, new_y, str[i]);
			new_x += char_size_x;
		}
	}
}
