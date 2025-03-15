#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include <windows.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define MAP_HEIGHT 30
#define MAP_WIDTH 10
#define BLOCK_SIZE 20
#define WW 1300
#define WH 700
#define NUM_RAYS 2400

typedef struct {
    float r, g, b, alpha;
} Color;

typedef struct { float x, y; } Position;
typedef struct { Position pos; float width, height; } rect_t;
typedef struct { Position pos; float radius; } circle_t;

// Colors
#define WHITE         (Color){1.0f, 1.0f, 1.0f, 1.0f}
#define BLACK         (Color){0.0f, 0.0f, 0.0f, 1.0f}
#define RED           (Color){1.0f, 0.0f, 0.0f, 1.0f}
#define GREEN         (Color){0.0f, 1.0f, 0.0f, 1.0f}
#define BLUE          (Color){0.0f, 0.0f, 1.0f, 1.0f}
#define BROWN         (Color){0.6f, 0.4f, 0.2f, 1.0f}
#define YELLOW        (Color){1.0f, 1.0f, 0.0f, 1.0f}
#define MAGENTA       (Color){1.0f, 0.0f, 1.0f, 1.0f}
#define CYAN          (Color){0.0f, 1.0f, 1.0f, 1.0f}
#define ORANGE        (Color){1.0f, 0.5f, 0.0f, 1.0f}
#define PURPLE        (Color){0.5f, 0.0f, 0.5f, 1.0f}
#define PINK          (Color){1.0f, 0.75f, 0.8f, 1.0f}
#define GRAY          (Color){0.5f, 0.5f, 0.5f, 1.0f}
#define LIME          (Color){0.75f, 1.0f, 0.0f, 1.0f}
#define TEAL          (Color){0.0f, 0.5f, 0.5f, 1.0f}
#define NAVY          (Color){0.0f, 0.0f, 0.5f, 1.0f}
#define DARK_GRAY     (Color){0.25f, 0.25f, 0.25f, 1.0f}

#define C_RAY_GROUND  (Color){0.0f, 0.5f, 0.0f, 1.0f}
#define C_RAY_SKY     (Color){0.5f, 0.8f, 1.0f, 1.0f}

#define C_RAY_WALL    (Color){0.56f, 0.51f, 0.44f, 1.0f}  // Grayish-brown
#define C_RAY_FLOOR   (Color){0.38f, 0.27f, 0.18f, 1.0f}  // Dark brown
#define C_RAY_CEILING (Color){0.07f, 0.07f, 0.14f, 1.0f}  // Very dark blue (almost black)

#endif
