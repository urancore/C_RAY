#ifndef _BIND_H
#define _BIND_H


typedef struct
{
	int key_code;
    void (*action)(void);
    char is_continuous;
} KeyBind;

extern KeyBind key_bindings[];

void move_forward(void);
void move_backward(void);
void strafe_right(void);
void strafe_left(void);
void rotate_left(void);
void rotate_right(void);
void quit_game(void);


#endif /* _BIND_H */
