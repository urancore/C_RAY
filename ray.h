#ifndef _RAY_H
#define _RAY_H

#define PI 3.14159265358979323846

#include <Windows.h>
#include <gl/gl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bind.h"

#define WHITE         (Color){1.0f, 1.0f, 1.0f}
#define BLACK         (Color){0.0f, 0.0f, 0.0f}
#define RED           (Color){1.0f, 0.0f, 0.0f}
#define GREEN         (Color){0.0f, 1.0f, 0.0f}
#define BLUE          (Color){0.0f, 0.0f, 1.0f}
#define BROWN         (Color){0.6f, 0.4f, 0.2f}
#define GROUND_GREEN  (Color){0.0f, 0.5f, 0.0f}
#define SKY_BLUE      (Color){0.5f, 0.8f, 1.0f}

#define DOOM_WALL     (Color){0.56f, 0.51f, 0.44f}  // Grayish-brown
#define DOOM_FLOOR    (Color){0.38f, 0.27f, 0.18f}  // Dark brown
#define DOOM_CEILING  (Color){0.07f, 0.07f, 0.14f}  // Very dark blue (almost black)

typedef struct {
	float r;
	float g;
	float b;
} Color;

typedef struct {
	float x;
	float y;
} Position;

typedef struct {
	Position pos;
	float width;
	float height;
} Rect;

typedef struct {
	Position pos;
	float radius;
} Circle;

typedef struct {
	Position pos;
	float angle;
	float fov;
	float sensitivity;
	float speed;
	float width;
	float height;
} Player;

#define MAP_HEIGHT  20
#define MAP_WIDTH   20
#define BLOCK_SIZE  20

#define WW 1024
#define WH 512

#define NUM_RAYS 264

// global vars declared in global.c
// keep in sync
extern unsigned char map[MAP_HEIGHT][MAP_WIDTH];
extern HWND window;
extern HDC hdc;
extern HGLRC hrc;

extern int last_mouse_x;
extern KeyBind key_bindings[];

extern Player player;

// input.c
void handle_keys_event(void);
void handle_mouse_movement(void);
void move_player(float angle);

// main.c
void HandleMouseClick(int x, int y);
void GL_Init(void);
void GL_Shutdown(void);

// map.c
void load_map(void);
void save_map(void);
void draw_mini_map(int size, Color player_color, Color player_line);

// misc.c
int check_collision(float x, float y);

// renderer.c
void r_drawRect(Rect *rect, Color color);
void r_drawPoint(int x, int y, int size, Color color);
void r_drawLine(int start_x, int start_y, int end_x, int end_y, float line_size, Color color);
void r_drawMap(unsigned char map[MAP_HEIGHT][MAP_WIDTH], Rect* mapArea);

#endif /* _RAY_H */
