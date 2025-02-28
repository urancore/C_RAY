typedef enum
{
    ev_keydown,
    ev_keyup,
    ev_mouse,
} evtype_t;

typedef struct
{
    evtype_t	type;
    int		data1;		// keys / mouse buttons
    int		data2;		// mouse x move
    int		data3;		// mouse y move
} event_t;
