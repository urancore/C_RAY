typedef struct
{
	char *name;
    void (*action)(void);
    char is_continuous;
	char is_pressed;
} Command;
