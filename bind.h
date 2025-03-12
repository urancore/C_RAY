#ifndef _BIND_H
#define _BIND_H

#define MAX_KEY_BINDINGS 124

typedef struct
{
	int key_code;
    void (*action)(void);
    char is_continuous;
	char is_pressed;
} KeyBind;

extern KeyBind key_bindings[MAX_KEY_BINDINGS];
extern int num_key_bindings;
void bind_key(int key, void (*key_func)(), int is_continuous, int is_pressed);

// funcs
void move_forward(void);
void move_backward(void);
void strafe_right(void);
void strafe_left(void);
void rotate_left(void);
void rotate_right(void);
void clip_cursor(void);

void quit_game(void);


#endif /* _BIND_H */
