#ifndef INPUT_H
#define INPUT_H

#include "../core/bind.h"
#include "../core/event.h"


extern KeyBind key_bindings[MAX_KEY_BINDINGS];

void i_handle_key_event(event_t event);
void i_handle_mouse_event(event_t event);

#endif
