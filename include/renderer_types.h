#ifndef RENDERER_TYPES_H
#define RENDERER_TYPES_H


#include "types.h"


typedef struct
{
    Position pos;
    int width;
    int height;
} Rect;


typedef struct
{
    Position pos;
    int radius;
} Circle;


#endif // RENDERER_TYPES_H

