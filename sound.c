#include "ray.h"

void play_sound(const char *filename)
{
	PlaySound(filename, NULL, SND_FILENAME);
}

void stop_sound() {
    PlaySound(NULL, NULL, 0);
}
