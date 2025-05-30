#ifndef TEXT_H
#define TEXT_H

#include "../core/core_types.h"

void init_font(void);
void r_sprint(int x, int y, char *str, size_t len_str, Color color);

#endif
