#ifndef EVENT_H
#define EVENT_H


#define C_RAY_KEYBOARD_EVENT 0
#define C_RAY_MOUSE_EVENT 1

typedef enum {
    ev_keydown,
    ev_keyup,
    ev_mouse,
} evtype_t;

typedef struct {
    evtype_t	type;
    int			key;	// keys / mouse buttons
    int			x;		// mouse x move
    int			y;		// mouse y move
} event_t;


void process_event(event_t event);
void get_events(event_t *events_buffer);

#endif
