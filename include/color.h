
#ifndef COLOR_H
#define COLOR_H


#define WHITE   (Color){1.0f, 1.0f, 1.0f}
#define BLACK   (Color){0.0f, 0.0f, 0.0f}
#define RED     (Color){1.0f, 0.0f, 0.0f}
#define GREEN   (Color){0.0f, 1.0f, 0.0f}
#define BLUE    (Color){0.0f, 0.0f, 1.0f}

#define DEFAULT_COLOR 255, 255, 255


typedef struct {
    float r;
    float g;
    float b;
} Color;


#endif
