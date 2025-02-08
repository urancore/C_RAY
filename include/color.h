
#ifndef COLOR_H
#define COLOR_H


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

#define DEFAULT_COLOR 255, 255, 255


typedef struct {
    float r;
    float g;
    float b;
} Color;


#endif
